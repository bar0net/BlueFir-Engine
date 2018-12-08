#ifndef BF_MODULES_EDITOR
#define BF_MODULES_EDITOR

#include "Module.h"
#include <vector>

namespace bluefir::editor
{
	class EditorPanel;
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

		// Event Handling
		void ProcessEvent(void* event) const;

	private:
		bool MainMenu();


	private:
		std::vector<editor::EditorPanel*> panels_;

		ImGuiIO* io = nullptr;
	};
}
#endif // !BF_MODULES_EDITOR

