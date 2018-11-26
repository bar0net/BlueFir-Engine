#ifndef BF_GRAPHICS_TEXTURE_BUFFER
#define BF_GRAPHICS_TEXTURE_BUFFER

#include "../Buffer.h"

namespace bluefir::graphics
{
	static unsigned int active_texture = 0;

	class TextureBuffer : public GLBuffer
	{
	public:
		TextureBuffer(unsigned int width, unsigned int height, unsigned int input_format = 0x1908, unsigned int store_format = 0x1908, char* data = nullptr);
		~TextureBuffer();

		void Bind() const override;
		void UnBind() const override;

		void SetParameter(unsigned int parameter, unsigned int value) const;

		unsigned int ID() const { return buffer_id_; }
	};
}

#endif // !BF_GRAPHICS_TEXTURE_BUFFER