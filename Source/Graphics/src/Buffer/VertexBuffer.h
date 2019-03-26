#ifndef BF_GRAPHICS_VERTEX_BUFFER
#define BF_GRAPHICS_VERTEX_BUFFER

#include "../Buffer.h"

#include <vector>

namespace bluefir::graphics
{
	static unsigned int active_vbo = 0;
	class VertexBuffer : public GLBuffer
	{
	public:
		VertexBuffer(const std::vector<float>* data);
		~VertexBuffer();

		void Bind() const override;
		void UnBind() const override;
	};
}

#endif // !BF_GRAPHICS_VERTEX_BUFFER

