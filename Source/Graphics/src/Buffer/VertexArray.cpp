#include "VertexArray.h"

#include "GL/glew.h"

#include "../BufferLayout.h"
#include "VertexBuffer.h"


bluefir::graphics::VertexArray::VertexArray(const VertexBuffer & vbo, const BufferLayout & layout)
{
	GLCall(glGenVertexArrays(1, &buffer_id_));
	
	GLCall(glBindVertexArray(buffer_id_));
	active_vao = buffer_id_;

	vbo.Bind();

	unsigned int offset = 0U;
	for (unsigned int i = 0U; i < layout.Elements().size(); i++)
	{
		const BufferElement element = layout.Elements()[i];
		if (element.count == 0U) continue;

		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized ? GL_TRUE : GL_FALSE, layout.Stride(), (const void*)offset));
		offset += element.count * BufferElement::SizeOfType(element.type);
	}
}

bluefir::graphics::VertexArray::~VertexArray()
{
	if (buffer_id_ == 0) return;

	if (active_vao == buffer_id_)
	{
		GLCall(glBindVertexArray(0));
		active_vao = 0U;
	}

	GLCall(glDeleteVertexArrays(1, &buffer_id_));
}

void bluefir::graphics::VertexArray::Bind() const
{
	if (active_vao == buffer_id_) return;

	GLCall(glBindVertexArray(buffer_id_));
	active_vao = buffer_id_;
}

void bluefir::graphics::VertexArray::UnBind() const
{
	if (active_vao != buffer_id_) return;

	GLCall(glBindVertexArray(0));
	active_vao = 0U;
}
