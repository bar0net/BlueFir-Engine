#include "ModuleResources.h"
#include "BaseMacros.h"

#include <vector>

#include "FileSystem.h"
#include "Importer.h"

#include "Resource/ResourceTexture.h"

// TODO: Maybe use something more sophisticated?
#include <random>

bool bluefir::modules::ModuleResources::Init()
{
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

			LOGINFO("File: %s", current_file.c_str());
		}
		files.erase(files.begin());
	}

	return true;
}

bool bluefir::modules::ModuleResources::CleanUp()
{
	for (auto it = resources_.begin(); it != resources_.end(); ++it)
		delete it->second;
	resources_.clear();

	return true;
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
	UID uid = Find(file_in_assets);

	if (force || uid == 0)
	{
		// Import
		char* data = nullptr;

		const char* extension = base::FileSystem::GetFileExtension(path.c_str());
		unsigned int size = resources::Importer::Texture(path.c_str(), &data);
		int width, height, depth, mips, bytes, format;
		resources::Importer::TextureInfo(data, size, &width, &height, &depth, &mips, &bytes, &format);

		if (size == 0)
		{
			LOGERROR("Error importing texture to library (%s)", path.c_str());
			return 0;
		}
		
		uid = GenerateNewUID();
		while (resources_.find(uid) != resources_.end()) uid = GenerateNewUID();
		
		// Check Save Folder Exists
		std::string save_path = BF_FILESYSTEM_LIBRARYDIR + std::string("/") + std::to_string(uid % 100);
		if (!base::FileSystem::ExistsDir(save_path.c_str()))
		{
			base::FileSystem::CreateDir(save_path.c_str());
		}

		// Save DDS to Library
		save_path += std::string("/") + std::to_string(uid) + std::string(".dds");
		if (base::FileSystem::ExportFile(save_path.c_str(), data, size))
		{
			// Create Resource
			resources::ResourceTexture* resource = new resources::ResourceTexture(uid, path.c_str(), save_path.c_str(), false);
			resource->width = width;
			resource->height = height;
			resource->depth = depth;
			resource->mips = mips;
			resource->bytes = bytes;
			resource->format = (resources::TextureFormat)format;

			resources_[uid] = resource;
			resources_[uid]->Save();
		}
		else
		{
			LOGERROR("Could not export texture to library (%s).", save_path.c_str());
			uid = 0U;
		}

		delete data; data = nullptr;
		return uid;
	}
	return uid;
}

UID bluefir::modules::ModuleResources::GenerateNewUID()
{
	static std::mt19937_64 generator;

	last_uid_ = generator();

	return last_uid_;
}

bluefir::resources::Resource * bluefir::modules::ModuleResources::CreateNewResource(int type, UID force_uid)
{
	return nullptr;
}
