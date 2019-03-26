#ifndef BF_EDITOR_PANELRENDERER
#define BF_EDITOR_PANELRENDERER

#include "../EditorPanel.h"

namespace bluefir::editor
{
	class PanelRenderer : public EditorPanel
	{
	public:
		PanelRenderer() : EditorPanel("Renderer Module") {}
		virtual ~PanelRenderer() {}

		virtual void Init() override;
		virtual void Draw() override;

	private:
		bool shader_panel = true;
	};
}

#endif // !BF_EDITOR_PANELRENDERER

