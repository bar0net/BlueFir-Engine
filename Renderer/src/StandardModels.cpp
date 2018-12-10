#include "StandardModels.h"

#include <vector>

#include "BufferLayout.h"
#include "Mesh.h"

#define BF_GRAPHICS_GRIDSIZE 100.0F

bluefir::graphics::Mesh* bluefir::graphics::StandardModels::Get(ModelList type)
{
	switch (type)	
	{
	case bluefir::graphics::ModelList::Triangle:
		return Triangle();
		break;
	case bluefir::graphics::ModelList::Quad:
		return Quad();
		break;
	case bluefir::graphics::ModelList::Cube:
		return Cube();
		break;
	case bluefir::graphics::ModelList::Grid:
		return Grid();
		break;
	default:
		break;
	}
	// Assert if we get an invalid model type
	ASSERT(false);

	return nullptr;
}

bluefir::graphics::Mesh * bluefir::graphics::StandardModels::Grid()
{
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	//vertices.resize(12 * (BF_GRAPHICS_GRIDSIZE + 1));
	//indices.resize(4 * (BF_GRAPHICS_GRIDSIZE + 1));

	for (int i = 0; i <= BF_GRAPHICS_GRIDSIZE; ++i)
	{
		vertices.emplace_back(-BF_GRAPHICS_GRIDSIZE); vertices.emplace_back(0.0F); vertices.emplace_back(i);
		vertices.emplace_back( BF_GRAPHICS_GRIDSIZE); vertices.emplace_back(0.0F); vertices.emplace_back(i);
		vertices.emplace_back(i); vertices.emplace_back(0.0F); vertices.emplace_back(-BF_GRAPHICS_GRIDSIZE); 
		vertices.emplace_back(i); vertices.emplace_back(0.0F); vertices.emplace_back( BF_GRAPHICS_GRIDSIZE);
		vertices.emplace_back(-BF_GRAPHICS_GRIDSIZE); vertices.emplace_back(0.0F); vertices.emplace_back(-i);
		vertices.emplace_back(BF_GRAPHICS_GRIDSIZE); vertices.emplace_back(0.0F); vertices.emplace_back(-i);
		vertices.emplace_back(-i); vertices.emplace_back(0.0F); vertices.emplace_back(-BF_GRAPHICS_GRIDSIZE);
		vertices.emplace_back(-i); vertices.emplace_back(0.0F); vertices.emplace_back(BF_GRAPHICS_GRIDSIZE);

		indices.emplace_back(8 * i); indices.emplace_back(8 * i + 1); indices.emplace_back(8 * i + 2); indices.emplace_back(8 * i + 3);
		indices.emplace_back(8 * i + 4); indices.emplace_back(8 * i + 5); indices.emplace_back(8 * i + 6); indices.emplace_back(8 * i + 7);
	}

	BufferLayout layout;
	layout.Push<float>(3);

	Mesh* model = new Mesh(vertices, indices, layout, MeshType::LINE);
	model->Build();

	return model;
}

bluefir::graphics::Mesh * bluefir::graphics::StandardModels::Triangle()
{
	std::vector<float> vertices = {
		0.0F,  1.0F,  0.0F,
		-1.0F, -1.0F,  0.0F,
		1.0F, -1.0F,  0.0F,
	};

	std::vector<unsigned int> indices = {
		0U, 1U, 2U
	};

	BufferLayout layout;
	layout.Push<float>(3);

	Mesh* model = new Mesh(vertices, indices, layout, MeshType::TRIANGLE);
	model->Build();

	return model;
}

bluefir::graphics::Mesh * bluefir::graphics::StandardModels::Quad()
{
	std::vector<float> vertices = {
		 1.0F,  1.0F,  0.0F,
		-1.0F,  1.0F,  0.0F,
		-1.0F, -1.0F,  0.0F,
		 1.0F, -1.0F,  0.0F,
	};

	std::vector<unsigned int> indices = {
		0U, 1U, 2U,
		0U, 2U, 3U
	};

	BufferLayout layout;
	layout.Push<float>(3);

	Mesh* model = new Mesh(vertices, indices, layout, MeshType::TRIANGLE);
	model->Build();

	return model;
}

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
		// TODO: CHECK ORDERS!!!
		/*2U, 1U, 0U,
		2U, 3U, 1U,*/
		6U, 2U, 0U,
		6U, 1U, 4U,
		/*6U, 4U, 5U,
		6U, 5U, 7U,
		7U, 5U, 1U,
		7U, 1U, 3U,
		0U, 1U, 5U,
		0U, 5U, 4U,
		3U, 2U, 6U,
		3U, 6U, 7U*/
	};

	BufferLayout layout;
	layout.Push<float>(3);

	Mesh* model = new Mesh(vertices, indices, layout, MeshType::TRIANGLE);
	model->Build();

	return model;
}