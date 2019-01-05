#include "PanelEditorView.h"

#include "../../Vendor/imgui-docking/imgui.h"

#include "../ModuleEditor.h"
#include "Input.h"

#include "GameObject.h"
#include "Components/Camera.h"
#include "Components/Transform.h"

// TODO: Change editor cam FOV on window resize, display scene on whole window (?)
#include "ModuleRenderer.h"

void bluefir::editor::PanelEditorView::Init()
{
}

void bluefir::editor::PanelEditorView::Draw()
{
	if (!enabled_) return;

	ImGui::Begin(name_.c_str(), &enabled_);

	if (ImGui::IsWindowFocused()) CameraControl();

	if (modules::ModuleEditor::getInstance().editor_camera_)
	{
		int id = modules::ModuleEditor::getInstance().editor_camera_->RenderTextureID();
		if (id != BF_INVALID_TEXTURE_ID)
		{
			float ratio = bluefir_renderer.GetAspectRatio();
			ImVec2 size = ImGui::GetContentRegionAvail();
			ImVec2 offset = size;

			if (size.x < ratio * size.y) size.y = size.x / ratio;
			else size.x = size.y * ratio;

			offset.x = 0.5F * (offset.x - size.x);
			offset.y = 0.5F * (offset.y - size.y);

			ImGui::Dummy(offset);
			if (offset.x > offset.y) ImGui::SameLine();
			ImGui::Image((ImTextureID)id, size, ImVec2(1,1), ImVec2(0,0));
		}
	}

	ImGui::End();
}

void bluefir::editor::PanelEditorView::CleanUp()
{
}

void bluefir::editor::PanelEditorView::CameraControl()
{
	core::Transform* t = modules::ModuleEditor::getInstance().go_editor_camera_->transform;

	// TODO
	if (bluefir_input.GetMouseWheel() != 0) LOGINFO("mouse wheel");
}
