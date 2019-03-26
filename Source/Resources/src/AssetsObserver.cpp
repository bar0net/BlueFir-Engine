#include "AssetsObserver.h"
#include "BaseMacros.h"

#include <queue>
#include <chrono>

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

	for (auto it = registered_assets.begin(); it != registered_assets.end(); ++it)
		delete it->second;
	registered_assets.clear();
}

void bluefir::resources::AssetsObserver::Start()
{
	asset_list = base::FileSystem::GetFilesInDir(BF_FILESYSTEM_ASSETSDIR, true);
	for (auto file : asset_list) AddAsset(file.c_str());
	
	run_thread = std::thread(&AssetsObserver::Run, this);
}


void bluefir::resources::AssetsObserver::Run()
{
	std::queue<AssetsFile*> pending;
	AssetsFile* current = nullptr;

	while (active)
	{
		bool modified = false;
		// Reset checked status
		for (auto it = registered_assets.begin(); it != registered_assets.end(); ++it) it->second->checked = false;

		// Retrieve list of assets
		std::vector<std::string> assets = base::FileSystem::GetFilesInDir(BF_FILESYSTEM_ASSETSDIR, true);

		// Check Modifications (and register checks)
		for (auto it = registered_assets.begin(); it != registered_assets.end(); ++it)
		{
			bool found = false;
			it->second->checked = true;
			for (auto jt = assets.begin(); jt != assets.end(); ++jt)
			{
				found = (it->first == *jt);
				if (found && it->second->HasChanged()) RegisterModification(*jt); 
				if (found)
				{
					assets.erase(jt); // delete file from discovered assets
					break;
				}
			}
		}

		// Remove unchecked assets
		for (auto it = registered_assets.begin(); it != registered_assets.end(); ++it)
		{
			if (!it->second->checked) { RegisterRemoval(it->first); modified = true; }
		}

		// Add remaining discovered assets
		for (auto jt = assets.begin(); jt != assets.end(); ++jt) { RegisterAddition(*jt); modified = true; }

		if (modified) UpdateAssetList();
		assets.clear();
	}
}

void bluefir::resources::AssetsObserver::RegisterAddition(std::string file)
{
	std::lock_guard<std::mutex> lock{ mutex };
	registered_assets[file] = new AssetsFile(file.c_str());
	to_add->push_back(file);
}

void bluefir::resources::AssetsObserver::RegisterRemoval(std::string file)
{
	std::lock_guard<std::mutex> lock{ mutex };
	delete registered_assets[file]; registered_assets.erase(file);
	to_remove->push_back(file);
}

void bluefir::resources::AssetsObserver::AddAsset(const char * file)
{
	registered_assets[file] = new AssetsFile(file);
}

void bluefir::resources::AssetsObserver::UpdateAssetList()
{
	std::lock_guard<std::mutex> lock{ mutex };
	asset_list = base::FileSystem::GetFilesInDir(BF_FILESYSTEM_ASSETSDIR, true);
}

std::vector<std::string> bluefir::resources::AssetsObserver::GetAssetList()
{
	std::lock_guard<std::mutex> lock{ mutex };
	return asset_list;
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
