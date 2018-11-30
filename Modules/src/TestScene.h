#ifndef BF_TESTING_SCENE
#define BR_TESTING_SCENE

#include "Module.h"

namespace bluefir::graphics
{
	struct Mesh;
}

namespace bluefir::modules
{

	class TestScene : public Module
	{
	public:
		UpdateState Update() override;
		bool CleanUp() override;

		bluefir::graphics::Mesh* cube;
	};

}
#endif // !BF_TESTING_SCENE

