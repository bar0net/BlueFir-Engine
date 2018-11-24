#include "FrameBuffer.h"

#include "GL/glew.h"


bluefir::graphics::FrameBuffer::FrameBuffer()
{
	GLCall(glGenFramebuffers(1, &idx));

	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, idx));
	active_fbo = idx;
}

bluefir::graphics::FrameBuffer::~FrameBuffer()
{
	if (idx == 0) return;

	if (active_fbo == idx)
	{
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		active_fbo = 0;
	}

	GLCall(glDeleteBuffers(1, &idx));
}

void bluefir::graphics::FrameBuffer::Bind() const
{
	if (active_fbo == idx) return;

	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, idx));
	active_fbo = idx;
}

void bluefir::graphics::FrameBuffer::UnBind() const
{
	if (active_fbo != idx) return;

	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	active_fbo = 0;
}

void bluefir::graphics::FrameBuffer::SetRenderBuffer(unsigned int renderID, unsigned int type) const
{
	Bind();
	GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, type, GL_RENDERBUFFER, renderID));
}

void bluefir::graphics::FrameBuffer::SetTexture(unsigned int textureID, unsigned int slot, unsigned int type) const
{
	Bind();
	GLCall(glFramebufferTexture(GL_FRAMEBUFFER, type + slot, textureID, slot));
}
