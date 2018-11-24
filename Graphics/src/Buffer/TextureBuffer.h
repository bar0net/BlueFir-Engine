#ifndef BF_GRAPHICS_TEXTURE_BUFFER
#define BF_GRAPHICS_TEXTURE_BUFFER

#include "../Buffer.h"

// TODO: Define the class

namespace bluefir::graphics
{
	static unsigned int active_ubo = 0;

	class TextureBuffer : public GLBuffer
	{
	public:
		TextureBuffer();
		~TextureBuffer();

		void Bind() const override;
		void UnBind() const override;
	};

}

#endif // !BF_GRAPHICS_TEXTURE_BUFFER