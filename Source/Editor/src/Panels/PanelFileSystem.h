#ifndef BF_EDITORPANELS_FILESYSTEM
#define BF_EDITORPANELS_FILESYSTEM

#include "../EditorPanel.h"
#include "LogSystem.h"
#include "FileSystem.h"

// TODO
namespace bluefir::editor
{
	class PanelFileSystem : public EditorPanel
	{
	public:
		PanelFileSystem() : EditorPanel("Explorer") { }
		virtual ~PanelFileSystem() {}

		virtual void Init() override;
		virtual void Draw() override;

	};
}
#endif // !BF_EDITORPANELS_FILESYSTEM
