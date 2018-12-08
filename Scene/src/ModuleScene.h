#ifndef BF_MODULES_SCENE
#define BF_MODULES_SCENE

#include "Module.h"

#include<unordered_map>

namespace bluefir::core
{
	class GameObject;
}

namespace bluefir::modules
{
	class ModuleScene : public Module
	{
	public:
		virtual ~ModuleScene();

		virtual bool Init() override;
		virtual UpdateState Update() override;
		virtual bool CleanUp() override;

		int CreateEmptyGameObject(const core::GameObject* parent = nullptr);

	private:
		int gameObject_counter_ = 0;
		std::unordered_map<int, core::GameObject*> gameObjects_;
	};
}


#endif // !BF_MODULES_SCENE

