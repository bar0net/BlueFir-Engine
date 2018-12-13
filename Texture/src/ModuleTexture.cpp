#include "ModuleTexture.h"

#include "FileSystem.h"
#include "Graphics.h"
#include "Buffer/TextureBuffer.h"

bool bluefir::modules::ModuleTexture::CleanUp()
{
	for (auto it = textures_.begin(); it != textures_.end(); ++it)
		delete it->second;
	textures_.clear();

	return true;
}

int bluefir::modules::ModuleTexture::LoadTexture(const char * filename)
{
	ASSERT(filename);
	LOGINFO("Loading Texture %s", filename);
	char* data = nullptr;
	int size = base::FileSystem::ImportFile(filename, data);
	if (size == 0)
	{
		LOGERROR("Could not import file: %s", filename);
		return -1;
	}

	graphics::TextureBuffer* texture = nullptr;
	// TODO: dynamically check texture format
	graphics::Graphics::ImportTexture(texture, data, size, "png");

	if (!texture)
	{
		LOGERROR("Could not infer image data from %s", filename);
		return -1;
	}

	textures_[texture->ID()] = texture;

	return texture->ID();
}

const bluefir::graphics::TextureBuffer* bluefir::modules::ModuleTexture::GetTextureBuffer(int id)
{
	if (textures_.find(id) == textures_.end())
	{
		LOGWARNING("Texture %i not found.", id);
		return nullptr;
	}

	return textures_[id];
}

bool bluefir::modules::ModuleTexture::RemoveTexture(int id)
{
	if (textures_.find(id) == textures_.end())
	{
		LOGWARNING("Texture %i not found.", id);
		return false;
	}

	delete textures_[id];
	textures_.erase(id);
	return true;
}
