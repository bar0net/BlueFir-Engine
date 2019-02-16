#include "Importer.h"

#include "FileSystem.h"
#include "LogSystem.h"
#include "Graphics.h"

#include "BaseMacros.h"


unsigned int bluefir::resources::Importer::Texture(const char * file_in_assets, char ** data)
{
	ASSERT(file_in_assets);

	if (*data != nullptr) 
	{ 
		delete *data; *data = nullptr; 
	}

	// Import data from assets 
	char* raw_image;
	unsigned int size = bluefir::base::FileSystem::ImportFile(file_in_assets, &raw_image);
	if (size == 0)
	{
		LOGERROR("An error has occurred while importing %s", std::string(file_in_assets));
		return false;
	}

	// Get file extension
	const char* extension = base::FileSystem::GetFileExtension(file_in_assets);

	// Convert to DDS
	unsigned int dds_size = graphics::Graphics::ConvertTexture(raw_image, size, data);

	return dds_size;
}

void bluefir::resources::Importer::TextureInfo(const char * data, int size, int * width, int * height, int * depth, int * mips, int * bytes, int * format)
{
	graphics::Graphics::TextureInfo(data, size, width, height, depth, mips, bytes, format); 
}
