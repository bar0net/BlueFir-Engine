#ifndef BF_EDITORPANELS_CONSOLE
#define BF_EDITORPANELS_CONSOLE

#include "../EditorPanel.h"
#include "LogSystem.h"

namespace bluefir::editor
{
	class PanelConsole : public EditorPanel
	{
	public:
		PanelConsole() : EditorPanel("Console") { memset(show_level_, true, BF_LOG_TYPECOUNT * sizeof(bool)); }
		virtual ~PanelConsole() {}

		virtual void Init() override;
		virtual void Draw() override;

	private:
		int SetButtonStyle(base::LogLevel type);

	private:
		unsigned int prev_log_size_ = 0U;
		bool show_level_[BF_LOG_TYPECOUNT];
	};
}
#endif // !BF_EDITORPANELS_CONSOLE
