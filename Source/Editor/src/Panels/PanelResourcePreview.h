#ifndef BF_EDITOR_PANEL_RESOURCE_PREVIEW
#define BF_EDITOR_PANEL_RESOURCE_PREVIEW

#include "../EditorPanel.h"
#include "BaseMacros.h"

namespace bluefir::resources
{
	class Resource;
}

namespace bluefir::editor
{
	class PanelResourcePreview : public EditorPanel
	{
	public:
		PanelResourcePreview() : EditorPanel("Preview") {}
		virtual ~PanelResourcePreview() = default;

		virtual void Init() {}
		virtual void Draw();
		virtual void CleanUp() {}
		virtual void Inspect() const {}

		void Set(UID uid);
		void Release();

	private:
		void DrawTexture();

	public:
		resources::Resource* resource = nullptr;
		bool resource_loaded = false;
	};
}

#endif // !BF_EDITOR_PANEL_RESOURCE_PREVIEW