#include "IndexBuffer.h"

#include "GL/glew.h"

bluefir::graphics::IndexBuffer::IndexBuffer(const std::vector<unsigned int>* data)
{
	GLCall(glGenBuffers(1, &idx));

	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idx));
	active_ibo = idx;

	elements = data->size();
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements * sizeof(unsigned int), data->data(), GL_STATIC_DRAW));
}

bluefir::graphics::IndexBuffer::~IndexBuffer()
{
	if (idx == 0) return;

	if (active_ibo == idx)
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
		active_ibo = 0;
	}

	glDeleteBuffers(1, &idx);
}

void bluefir::graphics::IndexBuffer::Bind() const
{
	if (active_ibo == idx) return;

	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idx));
	active_ibo = idx;
}

void bluefir::graphics::IndexBuffer::UnBind() const
{
	if (active_ibo != idx) return;

	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	active_ibo = 0;
}
