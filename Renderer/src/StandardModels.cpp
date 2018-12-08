#include "StandardModels.h"

#include <vector>

#include "BufferLayout.h"
#include "Mesh.h"

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
	default:
		break;
	}
	// Assert if we get an invalid model type
	ASSERT(false);

	return nullptr;
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

	Mesh* model = new Mesh(vertices, indices, layout);
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

	Mesh* model = new Mesh(vertices, indices, layout);
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
	model->Build();

	return model;
}