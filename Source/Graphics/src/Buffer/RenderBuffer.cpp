#include "RenderBuffer.h"

#include "GL/glew.h"

bluefir::graphics::RenderBuffer::RenderBuffer()
{
	GLCall(glGenRenderbuffers(1, &buffer_id_));

	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, buffer_id_));
	active_rbo = buffer_id_;
}

bluefir::graphics::RenderBuffer::~RenderBuffer()
{
	if (buffer_id_ == 0) return;

	if (active_rbo == buffer_id_)
	{
		GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
		active_rbo = 0U;
	}

	GLCall(glDeleteBuffers(1, &buffer_id_));
}

void bluefir::graphics::RenderBuffer::Bind() const
{
	if (active_rbo == buffer_id_) return;

	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, buffer_id_));
	active_rbo = buffer_id_;
}

void bluefir::graphics::RenderBuffer::UnBind() const
{
	if (active_rbo != buffer_id_) return;


	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
	active_rbo = 0U;
}

void bluefir::graphics::RenderBuffer::SetStorage(unsigned int width, unsigned int height, unsigned int component)
{
	Bind();
	GLCall(glRenderbufferStorage(GL_RENDERBUFFER, component, width, height));
}
