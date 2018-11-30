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
	struct WindowData
	{
		bool valid = false;
		SDL_Window* window = nullptr;
		SDL_Surface* surface = nullptr;
		void* context = nullptr;
	};

	static class Graphics
	{
	public:
		static WindowData* StartWindow(const char* title, unsigned int width, unsigned int height);
		static void SwapWindow(WindowData* data);
		static void DestroyWindow(WindowData* data);
		static void CreateViewport(unsigned int width, unsigned int height, float clear_color[4], float depth);
		static void ClearViewport();
		static void ChangeClearColor(float r, float g, float b, float a);
		static void ChangeClearColor(float clear_color[4]);
		static void GLClearErrors();
		static bool GLLogCall(const char* function, const char* file, int line);
		static void Draw(unsigned int count); // TODO: Define Draw
	};
}

#endif // !BF_GRAPHICS_H