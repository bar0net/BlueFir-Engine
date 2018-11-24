#ifndef BF_GRAPHICS_H
#define BF_GRAPHICS_H

#include <assert.h>

#if(BF_DEBUG)
	#define ASSERT(x)	assert(x)
	#define GLCall(x)	bluefir::graphics::Graphics::GLClearErrors();\
						x;\
						ASSERT(bluefir::graphics::Graphics::GLLogCall(#x, __FILE__, __LINE__));
#else
	#define ASSERT(x)	
	#define GLCall(x)	x
#endif

namespace bluefir::graphics
{
	class Graphics
	{
	public:
		static void GLClearErrors();
		static bool GLLogCall(const char* function, const char* file, int line);
	};
}

#endif // !BF_GRAPHICS_H