#ifndef BF_MODULES_EDITOR
#define BF_MODULES_EDITOR

#include "Module.h"
#include <vector>

namespace bluefir::editor
{
	class EditorPanel;
	class PanelInspector;
}

namespace bluefir::core
{
	class GameObject;
	class Camera;
}

struct ImGuiIO;

namespace bluefir::modules
{
	class ModuleEditor : public Module
	{
	public:
		virtual ~ModuleEditor();
		static ModuleEditor& getInstance() { static ModuleEditor instance_; return instance_; }

		virtual bool Init() override;
		virtual UpdateState PreUpdate() override;
		virtual UpdateState Update() override;
		virtual UpdateState PostUpdate() override;
		virtual bool CleanUp() override;

		// Accessors
		void SetInspectContent(const editor::EditorPanel* panel) { inspector_content_ = panel; }

		// Event Handling
		void ProcessEvent(void* event) const;

	private:
		bool MainMenu();


	private:
		std::vector<editor::EditorPanel*> panels_;
		editor::EditorPanel* inspector_ = nullptr;
		const editor::EditorPanel* inspector_content_ = nullptr;

		ImGuiIO* io = nullptr;

		core::GameObject* go_editor_camera_;
		core::Camera* editor_camera_;

		friend editor::PanelInspector;
	};
}
#endif // !BF_MODULES_EDITOR

