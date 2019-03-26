#ifndef BF_GRAPHICS_UNIFORM_BUFFER
#define BF_GRAPHICS_UNIFORM_BUFFER

#include "../Buffer.h"

namespace bluefir::graphics
{
	static unsigned int active_ubo = 0;

	// UniformBuffer assumes there are only 4x4 matrices
	// in the location std140 of the shader.
	class UniformBuffer : public GLBuffer
	{
	public:
		UniformBuffer(unsigned int buffer_size);
		virtual ~UniformBuffer();

		void Bind() const override;
		void UnBind() const override;

		void SetUniform(unsigned int offset, unsigned int data_size, const void* data) const;
	
	private:
		unsigned int buffer_size_;
	};

}

#endif // !BF_GRAPHICS_UNIFORM_BUFFER