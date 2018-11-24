#ifndef BF_GRAPHICS_UNIFORM_BUFFER
#define BF_GRAPHICS_UNIFORM_BUFFER

#include "../Buffer.h"

// TODO: Define the class

namespace bluefir::graphics
{
	static unsigned int active_ubo = 0;

	class UniformBuffer : public GLBuffer
	{
	public:
		UniformBuffer();
		~UniformBuffer();

		void Bind() const override;
		void UnBind() const override;
	};

}

#endif // !BF_GRAPHICS_UNIFORM_BUFFER