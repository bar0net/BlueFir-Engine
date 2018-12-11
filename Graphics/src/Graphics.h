#ifndef BF_GRAPHICS_H
#define BF_GRAPHICS_H

#include "BaseMacros.h"

#if(BF_DEBUG)
	#define GLCall(x)	bluefir::graphics::Graphics::GLClearErrors();\
						x;\
						ASSERT(bluefir::graphics::Graphics::GLLogCall(#x, __FILE__, __LINE__));
#else
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

	class Graphics
	{
	public:
		static WindowData* StartWindow(const char* title, unsigned int width, unsigned int height);
		static void SwapWindow(WindowData* data);
		static void DestroyWindow(WindowData* data);
		static unsigned int GetWindowID(WindowData* data);
		static void GetWindowSize(WindowData* data, int& width, int& height);

		static void CreateViewport(unsigned int width, unsigned int height, float clear_color[4], float depth);
		static void ChangeViewportSize(int width, int height);
		static void ClearViewport();

		static void ChangeClearColor(float r, float g, float b, float a);
		static void ChangeClearColor(float clear_color[4]);

		static void GLClearErrors();
		static bool GLLogCall(const char* function, const char* file, int line);

		static void Draw(unsigned int count);
		static void DrawLines(unsigned int count);

	private:
		Graphics() = delete;
		~Graphics() = delete;
	};
}

#endif // !BF_GRAPHICS_H