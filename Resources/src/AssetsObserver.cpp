#include "AssetsObserver.h"

#include <queue>
#include <chrono>

#include "FileSystem.h"

bluefir::resources::AssetsObserver::AssetsObserver() : root(new AssetsFile(BF_FILESYSTEM_ASSETSDIR))
{
	to_add = new std::vector<std::string>();
	to_remove = new std::vector<std::string>();

}

bluefir::resources::AssetsObserver::~AssetsObserver()
{
	active = false;
	if (run_thread.joinable()) run_thread.join();

	if (to_add != nullptr) delete to_add;
	if (to_remove != nullptr) delete to_remove;
	if (root != nullptr) delete root;
}


void bluefir::resources::AssetsObserver::Run()
{
	std::queue<AssetsFile*> pending;
	AssetsFile* current = nullptr;

	while (active)
	{
		if (pending.empty())
		{
			using namespace std::chrono_literals;
			std::this_thread::sleep_for(10ms);
			pending.push(root);
		}
		current = pending.front();
		pending.pop();

		if (current->isDir)
		{
			std::vector<std::string> hdd_contents = base::FileSystem::ReadDirectory(current->path.c_str());
			for (auto it = current->contents.begin(); it != current->contents.end(); ++it) it->second->checked = false;

			// Check Additions
			// Check if there is any file in hdd_contents that was not registered previously
			// or has changed in size / has been overwritten
			for (auto it = hdd_contents.begin(); it != hdd_contents.end(); ++it)
			{
				auto stored_content = current->contents.find(*it);
				if (stored_content == current->contents.end())
				{
					// Found a new file!
					if (base::FileSystem::IsDir(it->c_str()))
					{
						current->contents[*it] = new AssetsFile(it->c_str());
					}
					else
					{
						RegisterAddition(*it);
						current->contents[*it] = new AssetsFile(it->c_str(), base::FileSystem::FileSize(it->c_str()), base::FileSystem::FileModifiedTime(it->c_str()));
					}
				}
				else 
				{
					current->contents[*it]->checked = true;
					if (current->contents[*it]->isDir) continue;
					// Found existing file. 
					// Check if it has the same size and the same "last modified date" as the one registered
					if (current->contents[*it]->size != base::FileSystem::FileSize(it->c_str()) || current->contents[*it]->last_modified != base::FileSystem::FileModifiedTime(it->c_str()))
					{
						//RegisterRemoval(*it);
						RegisterAddition(*it);
						current->contents[*it]->size = base::FileSystem::FileSize(it->c_str());
						current->contents[*it]->last_modified = base::FileSystem::FileModifiedTime(it->c_str());
					}
				}
			}

			// Check Deletions
			// Check 
			for (auto it = current->contents.cbegin(); it != current->contents.cend();)
			{
				if (!it->second->checked)
				{
					DeleteContents(it->second);
					delete it->second;
					current->contents.erase(it++);
				}
				else
				{
					if (it->second->checked && it->second->isDir) pending.push(it->second);
					++it;
				}
			}
		}
	}
}

void bluefir::resources::AssetsObserver::DeleteContents(AssetsFile * file)
{
	if (file->isDir)
	{
		for (auto it = file->contents.begin(); it != file->contents.end(); ++it)
		{
			DeleteContents(it->second);
			delete it->second;
		}
		file->contents.clear();
	}
	else
	{
		RegisterRemoval(file->path);
	}
}

void bluefir::resources::AssetsObserver::RegisterAddition(std::string file)
{
	std::lock_guard<std::mutex> lock{ mutex };
	to_add->push_back(file);
}

void bluefir::resources::AssetsObserver::RegisterRemoval(std::string file)
{
	std::lock_guard<std::mutex> lock{ mutex };
	to_remove->push_back(file);
}

void bluefir::resources::AssetsObserver::GetAdditions(std::vector<std::string>** buffer)
{
	std::lock_guard<std::mutex> lock{ mutex };

	if (*buffer != nullptr)
	{
		delete *buffer; *buffer = nullptr;
	}

	*buffer = new std::vector<std::string>(*to_add);
	if (!to_add->empty()) to_add->clear();
}

void bluefir::resources::AssetsObserver::GetRemovals(std::vector<std::string>** buffer)
{
	std::lock_guard<std::mutex> lock{ mutex };

	if (*buffer != nullptr)
	{
		delete *buffer; *buffer = nullptr;
	}

	*buffer = new std::vector<std::string>(*to_remove);
	if (!to_remove->empty()) to_remove->clear();
}
