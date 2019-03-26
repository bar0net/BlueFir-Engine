#ifndef BF_GRAPHICS_RENDER_BUFFER
#define BF_GRAPHICS_RENDER_BUFFER

#include "../Buffer.h"

namespace bluefir::graphics
{
	static unsigned int active_rbo = 0;
	class RenderBuffer : public GLBuffer
	{
	public:
		RenderBuffer();
		~RenderBuffer();

		void Bind() const override;
		void UnBind() const override;

		unsigned int ID() { return buffer_id_; }

		void SetStorage(unsigned int width, unsigned int height, unsigned int component);
	};
}

#endif // !BF_GRAPHICS_RENDER_BUFFER