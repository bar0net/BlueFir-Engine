#ifndef BF_GRAPHICS_FRAME_BUFFER
#define BF_GRAPHICS_FRAME_BUFFER

#include "../Buffer.h"

#include <unordered_map>

namespace bluefir::graphics
{
	static unsigned int active_fbo = 0;
	
	class FrameBuffer : public GLBuffer
	{
	public:
		FrameBuffer();
		~FrameBuffer();

		void Bind() const override;
		void UnBind() const override;

		void SetRenderBuffer(unsigned int renderID, unsigned int type) const;
		void SetTexture(unsigned int textureID, unsigned int slot, unsigned int type) const;
	};

}

#endif // !BF_GRAPHICS_FRAME_BUFFER