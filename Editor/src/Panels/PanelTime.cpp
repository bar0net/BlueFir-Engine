#include "PanelTime.h"

#include "../../Vendor/imgui-docking/imgui.h"

#include "ModuleTime.h"
#include "MovingArray.h"

void bluefir::editor::PanelTime::Init()
{
	deltas_ = new base::MovingArray<float>(300, 0.0F);
	average_array_ = new base::MovingArray<float>(BF_EPT_AVG_COUNT, 0.0F);
}

void bluefir::editor::PanelTime::Draw()
{
	// TODO: Should make a RealDeltaTimeMS method to avoid dividing and multiplying by 1000
	float ms = modules::ModuleTime::getInstance().RealDeltaTime();
	deltas_->Push(1000.0F * ms);
	
	average_ += (ms - (*average_array_)[0]) / BF_EPT_AVG_COUNT;
	average_array_->Push(ms);

	if (!enabled_) return;
	ImGui::Begin(name_.c_str(), &enabled_);

	ImGui::Text("Execution time: %i:%f", (int)(modules::ModuleTime::getInstance().RealTime() / 60), std::fmodf(modules::ModuleTime::getInstance().RealTime(), 60));
	ImGui::Text("Running time: %fs", modules::ModuleTime::getInstance().Time());
	ImGui::Text("Unscaled Running time: %fs", modules::ModuleTime::getInstance().UnscaledTime());
	ImGui::Text("Time Scale: %f", modules::ModuleTime::getInstance().GetTimeScale());

	ImGui::PlotLines("Delta Time", base::MovingArray<float>::Get, deltas_, (int)deltas_->Size(), 1, "", 0, 100, ImVec2(0, 50));
	ImGui::Text("Average delta time: %fms", average_);

	ImGui::End();
}

void bluefir::editor::PanelTime::CleanUp()
{
	delete deltas_; deltas_ = nullptr;
}
