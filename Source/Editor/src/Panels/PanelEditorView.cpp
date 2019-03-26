#include "PanelEditorView.h"

#include "../../Vendor/imgui-docking/imgui.h"

#include "../ModuleEditor.h"

#include "Input.h"
#include "ModuleTime.h"

#include "GameObject.h"
#include "Components/Camera.h"
#include "Components/Transform.h"

// TODO: Change editor cam FOV on window resize, display scene on whole window (?)
#include "ModuleRenderer.h"

#define BF_VIEW_SPEED 2
#define BF_VIEW_ANGULAR 45

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
	float mov_speed = BF_VIEW_SPEED * bluefir_time.RealDeltaTime();
	float rot_speed = BF_VIEW_ANGULAR * bluefir_time.RealDeltaTime();
	
	if (bluefir_input.GetKey(core::KeyCode::LSHIFT)) { mov_speed *= 2; rot_speed *= 2; }

	// Linear Movement
	if (bluefir_input.GetKey(core::KeyCode::A)) t->LocalTranslate( mov_speed, 0, 0);
	if (bluefir_input.GetKey(core::KeyCode::D)) t->LocalTranslate(-mov_speed, 0, 0);

	if (bluefir_input.GetKey(core::KeyCode::W)) t->LocalTranslate(0,  mov_speed, 0);
	if (bluefir_input.GetKey(core::KeyCode::S)) t->LocalTranslate(0, -mov_speed, 0);

	if (bluefir_input.GetKey(core::KeyCode::Q)) t->LocalTranslate(0, 0,  mov_speed);
	if (bluefir_input.GetKey(core::KeyCode::E)) t->LocalTranslate(0, 0, -mov_speed);

	// Rotation
	if (bluefir_input.GetKey(core::KeyCode::J)) t->Rotate(0, -rot_speed, 0);
	if (bluefir_input.GetKey(core::KeyCode::L)) t->Rotate(0,  rot_speed, 0);

	if (bluefir_input.GetKey(core::KeyCode::I)) t->Rotate( rot_speed, 0, 0);
	if (bluefir_input.GetKey(core::KeyCode::K)) t->Rotate(-rot_speed, 0, 0);

	if (bluefir_input.GetKey(core::KeyCode::U)) t->Rotate(0, 0, -rot_speed);
	if (bluefir_input.GetKey(core::KeyCode::O)) t->Rotate(0, 0,  rot_speed);


	// TODO: Find a solution to avoid moving the window (when undocked) while moving the camera

	if (bluefir_input.GetMouseButton(core::MouseButton::MOUSE_MIDDLE))
	{
		float x, y;
		bluefir_input.GetMouseDisplacement(x, y);
		t->LocalTranslate(x, -y, 0);
	}

	if (bluefir_input.GetMouseButton(core::MouseButton::MOUSE_RIGHT) && !bluefir_input.GetMouseButton(core::MouseButton::MOUSE_LEFT))
	{
		float x, y;
		bluefir_input.GetMouseDisplacement(x, y);
		t->Rotate(y, x, 0);
	}


	if (bluefir_input.GetMouseWheel() != 0)
	{
		t->LocalTranslate(0, 0, (float)bluefir_input.GetMouseWheel() * bluefir_time.RealDeltaTime());
	}
}
