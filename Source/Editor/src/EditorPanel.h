#ifndef BF_EDITOR_PANEL
#define BF_EDITOR_PANEL

#include <string>

namespace bluefir::editor
{
	class EditorPanel
	{
	public:
		EditorPanel(const char* name) : name_(name) {}
		virtual ~EditorPanel() = default;

		virtual void Init() {}
		virtual void Draw() = 0;
		virtual void CleanUp() {}
		virtual void Inspect() const {}

	public:
		std::string name_;
		bool enabled_ = true;
	};
}

#endif // !BF_EDITOR_PANEL
