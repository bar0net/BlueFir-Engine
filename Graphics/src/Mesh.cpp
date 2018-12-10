#include "Mesh.h"

#include "Buffer/VertexBuffer.h"
#include "Buffer/VertexArray.h"
#include "Buffer/IndexBuffer.h"
#include "BufferLayout.h"


bluefir::graphics::Mesh::Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const BufferLayout & layout)
	: vertices_(vertices), indices_(indices), layout_(&layout), type_(MeshType::TRIANGLE)
{
}

bluefir::graphics::Mesh::Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const BufferLayout & layout, MeshType type)
	: vertices_(vertices), indices_(indices), layout_(&layout), type_(type)
{
	// TODO: Check the constructor is working properly
	// TODO: Maybe build mesh in the constructor (?)
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
}

void bluefir::graphics::Mesh::Build()
{
	vbo_ = new VertexBuffer(&vertices_);
	vao_ = new VertexArray(*vbo_, *layout_);
	ibo_ = new IndexBuffer(&indices_);
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
