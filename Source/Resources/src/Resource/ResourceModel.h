#ifndef _BF_RESOURCE_MODEL_
#define _BF_RESOURCE_MODEL_

#include "../Resource.h"

#include <vector>

class Mesh;
class Material;

namespace bluefir::resources
{
	class ResourceModel : public Resource
	{
	public:
		UID default_material_ = 0;
		std::vector<ResourceModel*> children;

		Mesh* model_mesh_ = nullptr;
		Material* model_material_ = nullptr;
	};
}

#endif // !_BF_RESOURCE_MODEL_
