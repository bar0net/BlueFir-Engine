#include "Graphics.h"

#include "GL/glew.h"
#include "GL/wglew.h"
#include "SDL.h"
#include "IL/il.h"
#include "IL/ilut.h"

#include "LogSystem.h"

#include "Buffer/TextureBuffer.h"

bluefir::graphics::WindowData* bluefir::graphics::Graphics::StartWindow(const char * title, unsigned int width, unsigned int height)
{
	assert(title);
	WindowData* data = new WindowData; 

	if (SDL_Init(SDL_INIT_VIDEO) != 0) return data;

	Uint32 flags = SDL_WINDOW_RESIZABLE;
	flags |= SDL_WINDOW_OPENGL;

	data->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
	data->surface = SDL_GetWindowSurface(data->window);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	data->context = SDL_GL_CreateContext(data->window);

	data->valid = data->context && data->surface && data->window;
	return data;
}

void bluefir::graphics::Graphics::SwapWindow(WindowData * data)
{
	ASSERT(data);
	SDL_GL_SwapWindow(data->window);
}

void bluefir::graphics::Graphics::DestroyWindow(WindowData * data)
{
	ASSERT(data);

	SDL_GL_DeleteContext(data->context);
	SDL_DestroyWindow(data->window);
	SDL_Quit();
}

unsigned int bluefir::graphics::Graphics::GetWindowID(WindowData * data)
{
	return (unsigned int)SDL_GetWindowID(data->window);
}

void bluefir::graphics::Graphics::GetWindowSize(WindowData * data, int & width, int & height)
{
	SDL_GetWindowSize(data->window, &width, &height);
}

void bluefir::graphics::Graphics::CreateViewport(unsigned int width, unsigned int height, float clear_color[4], float depth)
{
	glewInit();
	wglewInit();

	GLCall(glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glEnable(GL_CULL_FACE));
	GLCall(glFrontFace(GL_CCW));
	GLCall(glEnable(GL_TEXTURE_2D));

	GLCall(glClearDepth(1.0F));
	GLCall(glClearColor(clear_color[0], clear_color[1], clear_color[2], clear_color[3]));

	GLCall(glViewport(0, 0, width, height));
}

void bluefir::graphics::Graphics::ChangeViewportSize(int width, int height)
{
	GLCall(glViewport(0, 0, width, height));
}

void bluefir::graphics::Graphics::ClearViewport()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void bluefir::graphics::Graphics::ChangeClearColor(float r, float g, float b, float a)
{
	GLCall(glClearColor(r, g, b, a));
}

void bluefir::graphics::Graphics::ChangeClearColor(float clear_color[4])
{
	GLCall(glClearColor(clear_color[0], clear_color[1], clear_color[2], clear_color[3]));
}

void bluefir::graphics::Graphics::GLClearErrors()
{
#if BF_DEBUG
	GLenum error = glGetError();
#if BF_PLATFORM_WINDOWS
	if (error != GL_NO_ERROR) __debugbreak();
#else
	ASSERT(error == GL_NO_ERROR);
#endif // !Windows
#endif // !debug

	while (glGetError() != GL_NO_ERROR);
}

bool bluefir::graphics::Graphics::GLLogCall(const char * function, const char * file, int line)
{
	assert(function && file && line);
	GLenum error = glGetError();
	if (error == GL_NO_ERROR) return true;

	std::string s("OpenGL: <");
	s.append(file); s.append(" - "); s.append(function); s.append(": "); s += std::to_string(line); s.append("> ");

	switch (error)
	{
	case GL_INVALID_ENUM:
		s.append("Invalid Enum.");
		break;

	case GL_INVALID_VALUE:
		s.append("Invalid Value.");
		break;

	case GL_INVALID_OPERATION:
		s.append("Invalid Operation.");
		break;

	case GL_STACK_OVERFLOW:
		s.append("Stack Overflow.");
		break;

	case GL_STACK_UNDERFLOW:
		s.append("Stack Underflow.");
		break;

	case GL_OUT_OF_MEMORY:
		s.append("Out of memory.");
		break;

	case GL_INVALID_FRAMEBUFFER_OPERATION:
		s.append("Invalid frame buffer operation.");
		break;

	case GL_CONTEXT_LOST:
		s.append("Context lost.");
		break;

	case GL_TABLE_TOO_LARGE:
		s.append("Table too large.");
		break;

	default:
		s += std::to_string((int)error);
		break;
	}

	LOGERROR(s.c_str());
	s.clear();
	return false;
}

void bluefir::graphics::Graphics::Draw(unsigned int count)
{
	GLCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0));
}

void bluefir::graphics::Graphics::DrawLines(unsigned int count)
{
	GLCall(glDrawElements(GL_LINES, count, GL_UNSIGNED_INT, 0));
}

void bluefir::graphics::Graphics::ImportTexture(TextureBuffer* texture, const char* data, unsigned int size, const char* format)
{
	ASSERT(data);
	ILenum type = IL_PNG; // TODO: Parse type
	if (texture) delete texture; texture = nullptr;

	unsigned int imageID = 0;
	ilGenImages(1, &imageID);
	ilBindImage(imageID);

	ILboolean success = IL_TRUE;
	ILenum error;

	if (ilLoadL(type, data, size))
	{
		ILinfo ImageInfo;
		iluGetImageInfo(&ImageInfo);
		if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT) iluFlipImage();

		int channels = ilGetInteger(IL_IMAGE_CHANNELS);
		if (channels == 3) success = ilConvertImage(IL_RGB,  IL_UNSIGNED_BYTE);
		else if (channels == 4) success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

		if (success) 
		{
			ILubyte* content = ilGetData();
			int width = ilGetInteger(IL_IMAGE_WIDTH);
			int height = ilGetInteger(IL_IMAGE_HEIGHT);
			texture = new TextureBuffer(width, height, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_FORMAT), (char*)content);
			LOGINFO("Image imported successfully.");
		}
		else
		{
			LOGERROR("Image conversion on Texture Load failed.");
		}
		ilDeleteImages(1, &imageID);
	}
	else
	{
		error = ilGetError();
		LOGERROR("Could not read the image data. (IL reports error %i: %s", (int)error, iluErrorString(error));
		ASSERT(false);
	}
	ilBindImage(0);
}