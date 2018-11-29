#ifndef BF_GRAPHICS_MODELS
#define BF_GRAPHICS_MODELS

#include <vector>

namespace bluefir::graphics
{
	struct Model
	{
		std::vector<float> vertices;
		std::vector<unsigned int> indices;

		//Material* material;
	};

	static class ModelManager
	{
		Model* Cube();
	};
}

#endif // !BF_GRAPHICS_MODELS

