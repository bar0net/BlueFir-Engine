#include "TextureBuffer.h"

#include "GL/glew.h"

bluefir::graphics::TextureBuffer::TextureBuffer(unsigned int width, unsigned int height, unsigned int input_format, unsigned int store_format, char * data)
{
	GLCall(glGenTextures(1, &buffer_id_));
	GLCall(glBindTexture(GL_TEXTURE_2D, buffer_id_));
	active_texture = buffer_id_;
	
	if (data)
	{
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, input_format, width, height, 0, store_format, GL_UNSIGNED_BYTE, (void*)data));
	}
	else
	{
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, input_format, width, height, 0, store_format, GL_UNSIGNED_BYTE, NULL));
	}

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
}

bluefir::graphics::TextureBuffer::~TextureBuffer()
{
	if (active_texture == buffer_id_)
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
		active_texture = 0;
	}

	if (buffer_id_ != 0) GLCall(glDeleteTextures(1, &buffer_id_));
}

void bluefir::graphics::TextureBuffer::Bind() const
{
	if (active_texture == buffer_id_) return;

	GLCall(glBindTexture(GL_TEXTURE_2D, buffer_id_));
	active_texture = buffer_id_;
}

void bluefir::graphics::TextureBuffer::UnBind() const
{
	if (active_texture != buffer_id_) return;

	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	active_texture = 0;
}

void bluefir::graphics::TextureBuffer::SetParameter(unsigned int parameter, unsigned int value) const
{
	Bind();
	GLCall(glTexParameteri(GL_TEXTURE_2D, parameter, value));
}
