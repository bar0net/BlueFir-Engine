#ifndef BF_GRAPHICS_INDEX_BUFFER
#define BF_GRAPHICS_INDEX_BUFFER

#include "../Buffer.h"

#include <vector>

namespace bluefir::graphics
{
	static unsigned int active_ibo = 0;
	class IndexBuffer : public GLBuffer
	{
	public:
		IndexBuffer(const std::vector<unsigned int>* data);
		~IndexBuffer();

		void Bind() const override;
		void UnBind() const override;

		size_t elements = 0U;
	};
}

#endif // !BF_GRAPHICS_INDEX_BUFFER