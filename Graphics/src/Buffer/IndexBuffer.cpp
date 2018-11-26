#include "IndexBuffer.h"

#include "GL/glew.h"

bluefir::graphics::IndexBuffer::IndexBuffer(const std::vector<unsigned int>* data)
{
	GLCall(glGenBuffers(1, &buffer_id_));

	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id_));
	active_ibo = buffer_id_;

	elements = data->size();
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements * sizeof(unsigned int), data->data(), GL_STATIC_DRAW));
}

bluefir::graphics::IndexBuffer::~IndexBuffer()
{
	if (buffer_id_ == 0) return;

	if (active_ibo == buffer_id_)
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
		active_ibo = 0;
	}

	glDeleteBuffers(1, &buffer_id_);
}

void bluefir::graphics::IndexBuffer::Bind() const
{
	if (active_ibo == buffer_id_) return;

	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id_));
	active_ibo = buffer_id_;
}

void bluefir::graphics::IndexBuffer::UnBind() const
{
	if (active_ibo != buffer_id_) return;

	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	active_ibo = 0;
}
