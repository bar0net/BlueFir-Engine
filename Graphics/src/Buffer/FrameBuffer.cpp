#include "FrameBuffer.h"

#include "GL/glew.h"


bluefir::graphics::FrameBuffer::FrameBuffer()
{
	GLCall(glGenFramebuffers(1, &buffer_id_));

	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, buffer_id_));
	active_fbo = buffer_id_;
}

bluefir::graphics::FrameBuffer::~FrameBuffer()
{
	if (buffer_id_ == 0) return;

	if (active_fbo == buffer_id_)
	{
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		active_fbo = 0;
	}

	GLCall(glDeleteBuffers(1, &buffer_id_));
}

void bluefir::graphics::FrameBuffer::Bind() const
{
	if (active_fbo == buffer_id_) return;

	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, buffer_id_));
	active_fbo = buffer_id_;
}

void bluefir::graphics::FrameBuffer::UnBind() const
{
	if (active_fbo != buffer_id_) return;

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
