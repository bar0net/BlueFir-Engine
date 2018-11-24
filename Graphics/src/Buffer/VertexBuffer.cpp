#include "VertexBuffer.h"

#include "GL/glew.h"

bluefir::graphics::VertexBuffer::VertexBuffer(const std::vector<float>* data)
{
	GLCall(glGenBuffers(1, &idx));

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, idx));
	active_vbo = idx;

	GLCall(glBufferData(GL_ARRAY_BUFFER, data->size() * sizeof(float), data->data(), GL_STATIC_DRAW));
}

bluefir::graphics::VertexBuffer::~VertexBuffer()
{
	if (active_vbo == idx)
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		active_vbo = 0;
	}

	if (idx != 0) glDeleteBuffers(1, &idx);
}

void bluefir::graphics::VertexBuffer::Bind() const
{
	if (active_vbo == idx) return;

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, idx));
	active_vbo = idx;
}

void bluefir::graphics::VertexBuffer::UnBind() const
{
	if (active_vbo != idx) return;

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	active_vbo = 0;
}
