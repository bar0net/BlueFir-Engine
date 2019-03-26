#ifndef BF_GRAPHICS_VERTEX_ARRAY
#define BF_GRAPHICS_VERTEX_ARRAY

#include "../Buffer.h"

#include <vector>


namespace bluefir::graphics
{
	class VertexBuffer;
	class BufferLayout;

	static unsigned int active_vao = 0;
	class VertexArray : public GLBuffer
	{
	public:
		VertexArray(const VertexBuffer& vbo, const BufferLayout& layout);
		~VertexArray();

		void Bind() const override;
		void UnBind() const override;


	};
}

#endif // !BF_GRAPHICS_VERTEX_ARRAY