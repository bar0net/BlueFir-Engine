#include "PanelEditorView.h"

#include "../../Vendor/imgui-docking/imgui.h"

#include "Components/Camera.h"
#include "../ModuleEditor.h"

void bluefir::editor::PanelEditorView::Init()
{
}

void bluefir::editor::PanelEditorView::Draw()
{
	if (!enabled_) return;

	ImGui::Begin(name_.c_str(), &enabled_);

	if (modules::ModuleEditor::getInstance().editor_camera_)
	{
		int id = modules::ModuleEditor::getInstance().editor_camera_->RenderTextureID();
		if (id != BF_INVALID_TEXTURE_ID)
		{
			ImGui::Image((ImTextureID)id, ImVec2(1280, 720), ImVec2(1,1), ImVec2(0,0));
		}
	}

	ImGui::End();
}

void bluefir::editor::PanelEditorView::CleanUp()
{
}
