#include "Graphics.h"

#include "GL/glew.h"
#include "GL/wglew.h"

#include "LogSystem.h"


void bluefir::graphics::Graphics::GLClearErrors()
{
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
	s.append(">");

	LOGERROR(s.c_str());
	return false;
}
