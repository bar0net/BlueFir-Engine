#include "VertexBuffer.h"

#include "GL/glew.h"

bluefir::graphics::VertexBuffer::VertexBuffer(const std::vector<float>* data)
{
	GLCall(glGenBuffers(1, &buffer_id_));

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer_id_));
	active_vbo = buffer_id_;

	GLCall(glBufferData(GL_ARRAY_BUFFER, data->size() * sizeof(float), data->data(), GL_STATIC_DRAW));
}

bluefir::graphics::VertexBuffer::~VertexBuffer()
{
	if (active_vbo == buffer_id_)
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		active_vbo = 0;
	}

	if (buffer_id_ != 0) glDeleteBuffers(1, &buffer_id_);
}

void bluefir::graphics::VertexBuffer::Bind() const
{
	if (active_vbo == buffer_id_) return;

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer_id_));
	active_vbo = buffer_id_;
}

void bluefir::graphics::VertexBuffer::UnBind() const
{
	if (active_vbo != buffer_id_) return;

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	active_vbo = 0;
}
