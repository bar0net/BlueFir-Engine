#ifndef BF_CORE_RESOURCE_TEXTURE
#define BF_CORE_RESOURCE_TEXTURE

#include "../Resource.h"

namespace bluefir::resources
{
	enum class TextureFormat
	{
		UNKNOWN = 0,
		RGB,
		RGBA
	};

	class ResourceTexture : public Resource
	{
	public:
		ResourceTexture(UID id, const char* file, const char* exported_file, bool keep_in_memory = false) : Resource(id, file, exported_file, Type::TEXTURE, keep_in_memory) {}
		virtual ~ResourceTexture() {}

		bool LoadInMemory() override { return false; };
		void Save() const override;
		//void Load() override;

	public:
		unsigned int width = 0;
		unsigned int height = 0;
		unsigned int depth = 0;
		unsigned int mips = 0;
		unsigned int bytes = 0;
		unsigned int gpu_id = 0;
		TextureFormat format = TextureFormat::UNKNOWN;

	};
}

#endif // !BF_CORE_RESOURCE_TEXTURE
