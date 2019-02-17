#include "ModuleResources.h"
#include "BaseMacros.h"

#include <vector>

#include "FileSystem.h"
#include "Importer.h"

#include "Resource/ResourceTexture.h"
#include "AssetsObserver.h"

#define IS_IN_ASSETS(x) base::FileSystem::ExistsDir(x)

bool bluefir::modules::ModuleResources::Init()
{
	LOGINFO("Initializing Resource Module.");

	// Search and load all files in Library Folder
	std::vector<std::string> files = base::FileSystem::ReadDirectory(BF_FILESYSTEM_LIBRARYDIR);
	while (!files.empty())
	{
		std::string current_file = files[0];
		if (base::FileSystem::IsDir(current_file.c_str()))
		{
			std::vector<std::string> new_files = base::FileSystem::ReadDirectory(current_file.c_str());
			files.insert(files.end(), new_files.begin(), new_files.end());
		}
		else
		{
			std::string extension = base::FileSystem::GetFileExtension(current_file.c_str());
			resources::Resource* resource = nullptr;

			if (extension == "dds") resource = new resources::ResourceTexture(current_file.c_str());

			if (resource != nullptr)
			{
				// Check if this file is still in assets
				// if no meta file was found, GetFile returns 'INVALID_PATH'.
				if (IS_IN_ASSETS(resource->GetFile()))
				{
					LOGINFO("Resource found in library: %s", resource->GetFile());
					resources_[resource->GetUID()] = resource;
				}
				else 
				{
					this->DeleteResource(resource->GetUID());
					delete resource;
				}
			}
		}
		files.erase(files.begin());
	}

	observer = new resources::AssetsObserver();
	observer->Start();
	return true;
}

bool bluefir::modules::ModuleResources::CleanUp()
{
	LOGINFO("Closing Resource Module.");

	for (auto it = resources_.begin(); it != resources_.end(); ++it)
		delete it->second;
	resources_.clear();

	delete observer;
	return true;
}

bluefir::modules::UpdateState bluefir::modules::ModuleResources::PostUpdate()
{
	std::vector<std::string>* buffer = nullptr;
	
	observer->GetRemovals(&buffer);
	if (buffer)
	{
		for (auto it = buffer->begin(); it != buffer->end(); ++it)
		{
			LOGWARNING("IN REMOVE: %s", it->c_str());
		}
		delete buffer; buffer = nullptr;
	}

	observer->GetAdditions(&buffer);
	if (buffer)
	{
		for (auto it = buffer->begin(); it != buffer->end(); ++it)
		{
			LOGWARNING("IN ADD: %s", it->c_str());
		}
		delete buffer; buffer = nullptr;
	}

	return UpdateState::Update_Continue;
}

UID bluefir::modules::ModuleResources::Find(const char * file_in_assets) const
{
	ASSERT(file_in_assets);

	for (auto it = resources_.begin(); it != resources_.end(); ++it)
	{
		if (it->second->CheckFile(file_in_assets)) return it->second->GetUID();
	}

	return 0;
}

UID bluefir::modules::ModuleResources::ImportFile(const char * file_in_assets, bool force)
{
	ASSERT(file_in_assets);

	std::string path = BF_FILESYSTEM_ASSETSDIR + std::string("/") + file_in_assets;
	UID uid = Find(path.c_str());
	resources::Resource* resource = nullptr;

	if (force || uid == 0)
	{
		if (uid == 0) uid = GenerateNewUID();
		if (force) DeleteResource(uid);

		std::string extension = base::FileSystem::GetFileExtension(path.c_str());

		if (extension == "png") resource = resources::Importer::Texture(file_in_assets, uid);


		if (resource == nullptr)
		{
			LOGERROR("An error has occurred while importing %s.", path.c_str());
			return 0U;
		}
		else
		{
			LOGINFO("Successfully imported %s.", path.c_str());
			resource->Save();
			resources_[uid] = resource;
		}
	}
	else
	{
		LOGDEBUG("Using previously imported %s.", path.c_str());
	}

	return uid;
}

UID bluefir::modules::ModuleResources::GenerateNewUID()
{
	last_uid_ = generator();
	while (resources_.find(last_uid_) != resources_.end()) last_uid_ = generator();

	return last_uid_;
}

bluefir::resources::Resource * bluefir::modules::ModuleResources::CreateNewResource(int type, UID force_uid)
{
	return nullptr;
}

void bluefir::modules::ModuleResources::DeleteResource(UID uid)
{
	std::string file = resources_[uid]->GetExportedFile();
	std::string meta = file.substr(0, file.find_last_of(".")) + ".meta";

	base::FileSystem::DeleteFile(file.c_str());
	base::FileSystem::DeleteFile(meta.c_str());

	if (resources_.find(uid) == resources_.end()) return;

	delete resources_[uid]; resources_[uid] = nullptr;
	resources_.erase(uid);
}

void bluefir::modules::ModuleResources::DeleteResource(const char * exported_file)
{
	std::string file = exported_file;
	std::string meta = file.substr(0, file.find_last_of(".")) + ".meta";

	base::FileSystem::DeleteFile(file.c_str());
	base::FileSystem::DeleteFile(meta.c_str());
}
