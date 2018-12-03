#include "UniformBuffer.h"

#include "GL/glew.h"
#include "../Graphics.h"

bluefir::graphics::UniformBuffer::UniformBuffer(unsigned int buffer_size) : buffer_size_(buffer_size)
{
	GLCall(glGenBuffers(1, &buffer_id_));
	GLCall(glBindBuffer(GL_UNIFORM_BUFFER, buffer_id_));
	active_ubo = buffer_id_;

	GLCall(glBufferData(GL_UNIFORM_BUFFER, buffer_size_, NULL, GL_STREAM_DRAW));
	GLCall(glBindBufferRange(GL_UNIFORM_BUFFER, 0, buffer_id_, 0, buffer_size_));
}

bluefir::graphics::UniformBuffer::~UniformBuffer()
{
	UnBind();
	GLCall(glDeleteBuffers(1, &buffer_id_));
}

void bluefir::graphics::UniformBuffer::Bind() const
{
	if (active_ubo == buffer_id_) return;

	GLCall(glBindBuffer(GL_UNIFORM_BUFFER, buffer_id_));
	active_ubo = buffer_id_;
}

void bluefir::graphics::UniformBuffer::UnBind() const
{
	if (active_ubo != buffer_id_) return;

	GLCall(glBindBuffer(GL_UNIFORM_BUFFER, 0));
	active_ubo = 0;
}

// if data is a matrix, remember to pass it as COLUMN major!
void bluefir::graphics::UniformBuffer::SetUniform(unsigned int offset, unsigned int data_size, const void * data) const
{
	ASSERT(data);

	GLCall(glBindBufferRange(GL_UNIFORM_BUFFER, 0, buffer_id_, 0, buffer_size_));
	GLCall(glBindBuffer(GL_UNIFORM_BUFFER, buffer_id_));
	GLCall(glBufferSubData(GL_UNIFORM_BUFFER, offset, data_size, data));
}
