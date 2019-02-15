#include "ModuleResources.h"
#include "BaseMacros.h"

#include "FileSystem.h"
#include "Importer.h"

#include "Resource/ResourceTexture.h"

// TODO: Maybe use something more sophisticated?
#include <random>

UID bluefir::modules::ModuleResources::Find(const char * file_in_assets) const
{
	ASSERT(file_in_assets);

	return 0;
}

UID bluefir::modules::ModuleResources::ImportFile(const char * file_in_assets, bool force)
{
	ASSERT(file_in_assets);
	std::string path = BF_FILESYSTEM_ASSETSDIR + std::string("/") + file_in_assets;

	if (force || Find(file_in_assets) > 0)
	{
		// Import
		char* data = nullptr;

		const char* extension = base::FileSystem::GetFileExtension(path.c_str());
		unsigned int size = resources::Importer::Texture(path.c_str(), &data);
		if (size == 0)
		{
			LOGERROR("Error importing texture to library (%s)", path.c_str());
			return 0;
		}
		
		UID uid = GenerateNewUID();
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
			resources_[uid] = new resources::ResourceTexture(uid, path.c_str(), save_path.c_str(), false);
		}
		else
		{
			LOGERROR("Could not export texture to library (%s).", save_path.c_str());
			uid = 0U;
		}

		delete data; data = nullptr;
		return uid;
	}
	return 0;
}

UID bluefir::modules::ModuleResources::GenerateNewUID()
{
	static std::mt19937_64 generator;

	return generator();
}

bluefir::resources::Resource * bluefir::modules::ModuleResources::CreateNewResource(int type, UID force_uid)
{
	return nullptr;
}
