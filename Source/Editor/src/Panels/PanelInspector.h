#ifndef BF_EDITORPANELS_INSPECTOR
#define BF_EDITORPANELS_INSPECTOR

#include "../EditorPanel.h"

namespace bluefir::editor
{
	class PanelInspector : public EditorPanel
	{
	public:
		PanelInspector() : EditorPanel("Inspector") {}
		virtual ~PanelInspector() {}

		virtual void Init() override;
		virtual void Draw() override;
	};
}
#endif // !BF_EDITORPANELS_INSPECTOR
