#ifndef BF_EDITORPANELS_TEXTURE
#define BF_EDITORPANELS_TEXTURE

#include "../EditorPanel.h"

//  TODO: DO THIS!
namespace bluefir::core
{
	class GameObject;
}

namespace bluefir::editor
{
	class PanelTexture : public EditorPanel
	{
	public:
		PanelTexture() : EditorPanel("Module Textures") {}
		virtual ~PanelScene() {}

		virtual void Init() override;
		virtual void Draw() override;
		virtual void CleanUp() override;
		virtual void Inspect() const override;
	};
}
#endif // !BF_EDITORPANELS_TEXTURE