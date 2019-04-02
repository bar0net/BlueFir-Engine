#ifndef BF_CORE_RESOURCE_TEXTURE
#define BF_CORE_RESOURCE_TEXTURE

#include "../Resource.h"

namespace bluefir::graphics
{
	class TextureBuffer;
}

namespace bluefir::resources
{
	// Using same format codes from DevIL "il.h"
	// for convenience
	enum class TextureFormat
	{
		UNKNOWN = 0,
		COLOUR_INDEX	= 0x1900,
		COLOR_INDEX		= 0x1900,
		ALPHA			= 0x1906,
		RGB				= 0x1907,
		RGBA			= 0x1908,
		BGR				= 0x80E0,
		BGRA			= 0x80E1,
		LUMINANCE		= 0x1909,
		LUMINANCE_ALPHA = 0x190A
	};

	class ResourceTexture : public Resource
	{
	public:
		// TODO: Solve if meta has been erased previous to load.
		ResourceTexture(const char* exported_file) : Resource(exported_file) { this->Load(); }
		ResourceTexture(UID id, const char* file, const char* exported_file, bool keep_in_memory = false) : Resource(id, file, exported_file, Type::TEXTURE, keep_in_memory) {}
		~ResourceTexture();

		bool LoadInMemory() override;
		bool UnloadFromMemory(bool force = false) override;

		void Save() const override;
		void Load() override;
		void Set(unsigned int width, unsigned int height, unsigned int depth, unsigned int mips, unsigned int bytes, int format);

	public:
		unsigned int width = 0;
		unsigned int height = 0;
		unsigned int depth = 0;
		unsigned int mips = 0;
		unsigned int bytes = 0;
		unsigned int gpu_id = 0;
		TextureFormat format = TextureFormat::UNKNOWN;

	private:
		graphics::TextureBuffer* buffer_ = nullptr;
	};
}

#endif // !BF_CORE_RESOURCE_TEXTURE
