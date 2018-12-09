#include "PanelInspector.h"

#include "../ModuleEditor.h"
#include "../../Vendor/imgui-docking/imgui.h"

void bluefir::editor::PanelInspector::Init()
{
}

void bluefir::editor::PanelInspector::Draw()
{
	if (!enabled_) return;
	ImGui::Begin("Inspector", &enabled_);

	if (modules::ModuleEditor::getInstance().inspector_content_)
		modules::ModuleEditor::getInstance().inspector_content_->Inspect();

	ImGui::End();
}
