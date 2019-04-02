#include "Importer.h"

#include "FileSystem.h"
#include "LogSystem.h"
#include "Graphics.h"

#include "BaseMacros.h"

#include "Resource.h"
#include "Resource/ResourceTexture.h"

bluefir::resources::Resource * bluefir::resources::Importer::Import(const char * file_in_assets, UID uid, unsigned int type)
{
	switch ((resources::Type)type)
	{
	case resources::Type::TEXTURE:
		return Texture(file_in_assets, uid);
		break;

	default:
		break;
	}
	return nullptr;
}

bluefir::resources::Resource* bluefir::resources::Importer::Texture(const char * file_in_assets, UID uid)
{
	ASSERT(file_in_assets);
	//std::string file = BF_FILESYSTEM_ASSETSDIR + std::string("/") + file_in_assets;
	std::string file =  file_in_assets;
	resources::ResourceTexture* resource = nullptr;
	char* raw_image = nullptr;
	char* dds_image = nullptr;

	// Import data from assets 
	unsigned int size = bluefir::base::FileSystem::ImportFile(file.c_str(), &raw_image);
	if (size == 0)
	{
		base::FileSystem::ReleaseFile(&raw_image);
		LOGERROR("An error has occurred while importing %s", std::string(file_in_assets));
		return nullptr;
	}

	// Get file extension
	const char* extension = base::FileSystem::GetFileExtension(file_in_assets);

	// Convert to DDS
	unsigned int dds_size = graphics::Graphics::ConvertTexture(raw_image, size, &dds_image);

	// Get Save Folder
	std::string save_folder = GetSaveFolder(uid);
	std::string filename = save_folder + std::string("/") + std::to_string(uid) + std::string(".dds");

	// Save DDS to Library
	if (base::FileSystem::ExportFile(filename.c_str(), dds_image, dds_size))
	{
		// Create Resource
		int format;
		resource = new resources::ResourceTexture(uid, file.c_str(), filename.c_str(), false);
		graphics::Graphics::TextureInfo(dds_image, dds_size, &resource->width, &resource->height, &resource->depth, &resource->mips, &resource->bytes, &format);
		resource->format = (TextureFormat)format;
	}
	else LOGERROR("Could not export texture to library (%s).", filename.c_str());

	bluefir::base::FileSystem::ReleaseFile(&raw_image);
	bluefir::base::FileSystem::ReleaseFile(&dds_image);

	return resource;
}

std::string bluefir::resources::Importer::GetSaveFolder(UID uid)
{
	std::string save_path = BF_FILESYSTEM_LIBRARYDIR + std::string("/") + std::to_string(uid).substr(0,2);
	if (!base::FileSystem::ExistsDir(save_path.c_str()))
	{
		base::FileSystem::CreateDir(save_path.c_str());
	}
	return save_path;
}
