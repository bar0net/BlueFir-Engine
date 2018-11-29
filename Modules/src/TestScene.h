#ifndef BF_TESTING_SCENE
#define BR_TESTING_SCENE

#include "Module.h"

namespace bluefir::modules
{
	struct graphics::Model;

	class TestScene : public Module
	{
	public:
		UpdateState Update() override;
		bool CleanUp() override;

		const graphics::Model* cube;
	};

}
#endif // !BF_TESTING_SCENE

