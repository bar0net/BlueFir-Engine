#include "RenderBuffer.h"

#include "GL/glew.h"

bluefir::graphics::RenderBuffer::RenderBuffer()
{
	GLCall(glGenRenderbuffers(1, &idx));

	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, idx));
	active_rbo = idx;
}

bluefir::graphics::RenderBuffer::~RenderBuffer()
{
	if (idx == 0) return;

	if (active_rbo == idx)
	{
		GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
		active_rbo = 0U;
	}

	GLCall(glDeleteBuffers(1, &idx));
}

void bluefir::graphics::RenderBuffer::Bind() const
{
	if (active_rbo == idx) return;

	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, idx));
	active_rbo = idx;
}

void bluefir::graphics::RenderBuffer::UnBind() const
{
	if (active_rbo != idx) return;


	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
	active_rbo = 0U;
}

void bluefir::graphics::RenderBuffer::SetStorage(unsigned int width, unsigned int height, unsigned int component)
{
	Bind();
	GLCall(glRenderbufferStorage(GL_RENDERBUFFER, component, width, height));
}
