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

struct SDL_Window;
struct SDL_Surface;

namespace bluefir::graphics
{
	struct Color
	{
		float r = 1.0f;
		float g = 1.0f;
		float b = 1.0f;
		float a = 1.0f;
	};

	struct WindowData
	{
		bool valid = false;
		SDL_Window* window = nullptr;
		SDL_Surface* surface = nullptr;
		void* context = nullptr;
	};

	class Graphics
	{
	public:
		static WindowData* StartWindow(const char* title, unsigned int width, unsigned int height);
		static void CreateViewport(unsigned int width, unsigned int height, Color clear_color, float depth);
		static void ClearViewport();
		static void ChangeClearColor(float r, float g, float b, float a);
		static void GLClearErrors();
		static bool GLLogCall(const char* function, const char* file, int line);
	};
}

#endif // !BF_GRAPHICS_H