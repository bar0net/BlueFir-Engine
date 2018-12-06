#ifndef BF_MODULES_SCENE
#define BF_MODULES_SCENE

#include "Module.h"
#include <vector>

namespace bluefir::core
{
	class GameObject;
}

namespace bluefir::modules
{
	class ModuleScene : public Module
	{
	public:
		ModuleScene();
		virtual ~ModuleScene();

		virtual bool Start() override;
		virtual UpdateState Update() override;

	public:
		std::vector<const core::GameObject*> gameObjects_;
	};
}

#endif // !BF_MODULES_SCENE

