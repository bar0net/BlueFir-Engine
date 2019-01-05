#ifndef BF_EDITORPANELS_SCENEVIEW
#define BF_EDITORPANELS_SCENEVIEW

#include "../EditorPanel.h"

#define BF_EPT_AVG_COUNT 15

namespace bluefir::editor
{
	class PanelEditorView : public EditorPanel
	{
	public:
		PanelEditorView() : EditorPanel("Scene") {}
		virtual ~PanelEditorView() {}

		virtual void Init() override;
		virtual void Draw() override;
		virtual void CleanUp() override;

	private:
		void CameraControl();
	};
}
#endif // !BF_EDITORPANELS_SCENEVIEW