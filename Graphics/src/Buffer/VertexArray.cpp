#include "VertexArray.h"

#include "GL/glew.h"

#include "../BufferLayout.h"
#include "VertexBuffer.h"


bluefir::graphics::VertexArray::VertexArray(const VertexBuffer & vbo, const BufferLayout & layout)
{
	GLCall(glGenVertexArrays(1, &idx));
	
	GLCall(glBindVertexArray(idx));
	active_vao = idx;

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
	if (idx == 0) return;

	if (active_vao == idx)
	{
		GLCall(glBindVertexArray(0));
		active_vao = 0U;
	}

	GLCall(glDeleteVertexArrays(1, &idx));
}

void bluefir::graphics::VertexArray::Bind() const
{
	if (active_vao == idx) return;

	GLCall(glBindVertexArray(idx));
	active_vao = idx;
}

void bluefir::graphics::VertexArray::UnBind() const
{
	if (active_vao != idx ) return;

	GLCall(glBindVertexArray(0));
	active_vao = 0U;
}
