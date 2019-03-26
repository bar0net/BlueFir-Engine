#ifndef BF_EDITORPANELS_TIME
#define BF_EDITORPANELS_TIME

#include "../EditorPanel.h"

#define BF_EPT_AVG_COUNT 15

namespace bluefir::base
{
	template <class T> class MovingArray;
}

namespace bluefir::editor
{
	class PanelTime : public EditorPanel
	{
	public:
		PanelTime() : EditorPanel("Time Module") {}
		virtual ~PanelTime() {}

		virtual void Init() override;
		virtual void Draw() override;
		virtual void CleanUp() override;

	private:
		base::MovingArray<float>* deltas_ = nullptr;
		base::MovingArray<float>* average_array_ = nullptr;
		float average_ = 0.0F;
	};
}
#endif // !BF_EDITORPANELS_TIME
