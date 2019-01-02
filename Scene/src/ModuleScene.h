#ifndef BF_MODULES_SCENE
#define BF_MODULES_SCENE

#include "Module.h"

#include<unordered_map>

namespace bluefir::core
{
	class GameObject;
	class Camera;
}

namespace bluefir::editor
{
	class PanelScene;
}

namespace bluefir::modules
{
	class ModuleScene : public Module
	{
	public:
		ModuleScene();
		virtual ~ModuleScene();
		static ModuleScene& getInstance() { static ModuleScene instance_; return instance_; }

		virtual bool Init() override;
		virtual UpdateState Update() override;
		virtual bool CleanUp() override;

		int CreateEmptyGameObject(core::GameObject* parent = nullptr);

	public:
		core::GameObject* root_ = nullptr;

	private:
		int gameObject_counter_ = 0;
		std::unordered_map<int, core::GameObject*> gameObjects_;


		friend bluefir::editor::PanelScene;
	};
}


#endif // !BF_MODULES_SCENE

