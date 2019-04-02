#ifndef BF_EDITORPANELS_RESOURCES
#define BF_EDITORPANELS_RESOURCES

#include "../EditorPanel.h"

namespace bluefir::editor
{
	class PanelResources : public EditorPanel
	{
	public:
		PanelResources() : EditorPanel("Resources Module") {}
		virtual ~PanelResources() {}

		virtual void Init() override;
		virtual void Draw() override;

	private:
		std::string selected_asset;
		unsigned long long int selected_uid = 0;
	};
}
#endif // !BF_EDITORPANELS_RESOURCES
