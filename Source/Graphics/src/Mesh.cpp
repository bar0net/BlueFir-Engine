#include "Mesh.h"

#include "BaseMacros.h"

#include "Buffer/VertexBuffer.h"
#include "Buffer/VertexArray.h"
#include "Buffer/IndexBuffer.h"
#include "BufferLayout.h"

#include "LogSystem.h"


bluefir::graphics::Mesh::Mesh(const std::vector<float>* vertices, const std::vector<unsigned int>* indices, const BufferLayout* layout)
	: vertices_(vertices), indices_(indices), layout_(layout), type_(MeshType::TRIANGLE)
{
}

bluefir::graphics::Mesh::Mesh(const std::vector<float>* vertices, const std::vector<unsigned int>* indices, const BufferLayout* layout, MeshType type)
	: vertices_(vertices), indices_(indices), layout_(layout), type_(type)
{
	// TODO: Check the constructor is working properly
	// TODO: Maybe build mesh in the constructor (?)
	// TODO: Passing the layout by ref doesn't work. It gets destroid at the end of the caller's scope, dummy!
}

bluefir::graphics::Mesh::~Mesh()
{
	if (vbo_ != nullptr)
	{
		delete vbo_;
		vbo_ = nullptr;
	}

	if (ibo_ != nullptr)
	{
		delete ibo_;
		ibo_ = nullptr;
	}

	if (vao_ != nullptr)
	{
		delete vao_;
		vao_ = nullptr;
	}

	if (layout_ != nullptr)
	{
		delete layout_;
		layout_ = nullptr;
	}

	if (vertices_)
	{
		delete vertices_;
		vertices_ = nullptr;
	}

	if (indices_)
	{
		delete indices_;
		indices_ = nullptr;
	}
}

void bluefir::graphics::Mesh::Build()
{
	vbo_ = new VertexBuffer(vertices_);
	vao_ = new VertexArray(*vbo_, *layout_);
	ibo_ = new IndexBuffer(indices_);
}

void bluefir::graphics::Mesh::Bind() const
{
	ASSERT(vao_ && ibo_);
	vao_->Bind();
	ibo_->Bind();
}

void bluefir::graphics::Mesh::UnBind() const
{
	ASSERT(vao_ && ibo_);
	ibo_->UnBind();
	vao_->UnBind();
}
