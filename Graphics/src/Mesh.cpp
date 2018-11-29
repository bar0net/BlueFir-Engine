#include "Mesh.h"

#include "Buffer/VertexBuffer.h"
#include "Buffer/VertexArray.h"
#include "Buffer/IndexBuffer.h"
#include "BufferLayout.h"

bluefir::graphics::Mesh* bluefir::graphics::StandardModels::Cube()
{
	std::vector<float> vertices = {
		 1.0F,  1.0F,  1.0F,
		 1.0F,  1.0F, -1.0F,
		 1.0F, -1.0F,  1.0F,
		 1.0F, -1.0F, -1.0F,
		-1.0F,  1.0F,  1.0F,
		-1.0F,  1.0F, -1.0F,
		-1.0F, -1.0F,  1.0F,
		-1.0F, -1.0F, -1.0F,
	};

	std::vector<unsigned int> indices = {
		2U, 1U, 0U,
		2U, 3U, 1U,
		6U, 2U, 0U,
		6U, 1U, 4U,
		6U, 4U, 5U,
		6U, 5U, 7U,
		7U, 5U, 1U,
		7U, 1U, 3U,
		0U, 1U, 5U,
		0U, 5U, 4U,
		3U, 2U, 6U,
		3U, 6U, 7U
	};

	BufferLayout layout;
	layout.Push<float>(3);

	Mesh* model = new Mesh(vertices, indices, layout);

	return model;
}

bluefir::graphics::Mesh::Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const BufferLayout & layout)
	: vertices_(vertices), indices_(indices), layout_(layout)
{
	// TODO: Check the constructor is working properly
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
}

void bluefir::graphics::Mesh::Build()
{
	vbo_ = new VertexBuffer(&vertices_);
	vao_ = new VertexArray(*vbo_, *layout_);
	ibo_ = new IndexBuffer(&indices_);
}

void bluefir::graphics::Mesh::Bind()
{
	vao_->Bind();
	ibo_->Bind();
}

void bluefir::graphics::Mesh::UnBind()
{
	ibo_->UnBind();
	vao_->UnBind();
}