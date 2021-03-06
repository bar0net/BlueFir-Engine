#ifndef BF_EDITORPANELS_SCENE
#define BF_EDITORPANELS_SCENE

#include "../EditorPanel.h"

namespace bluefir::core
{
	class GameObject;
}

namespace bluefir::editor
{
	class PanelScene : public EditorPanel
	{
	public:
		PanelScene() : EditorPanel("Hierarchy") {}
		virtual ~PanelScene() {}

		virtual void Init() override;
		virtual void Draw() override;
		virtual void CleanUp() override;
		virtual void Inspect() const override;

	private:
		void DisplayGameObject(const core::GameObject* go, int level = 0);
		void SetSelectedObject(const core::GameObject* go);

	private:
		const core::GameObject* selected_ = nullptr;
	};
}
#endif // !BF_EDITORPANELS_SCENE
