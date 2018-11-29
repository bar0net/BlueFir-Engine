#include "ModelManager.h"

bluefir::graphics::Model* bluefir::graphics::ModelManager::Cube()
{
	Model* model = new Model();
	model->vertices = {
		 1.0F,  1.0F,  1.0F,
		 1.0F,  1.0F, -1.0F,
		 1.0F, -1.0F,  1.0F,
		 1.0F, -1.0F, -1.0F,
		-1.0F,  1.0F,  1.0F,
		-1.0F,  1.0F, -1.0F,
		-1.0F, -1.0F,  1.0F,
		-1.0F, -1.0F, -1.0F,
	};

	model->indices = {
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

	return model;
}
