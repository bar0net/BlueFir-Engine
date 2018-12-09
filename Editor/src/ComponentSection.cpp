#include "ComponentSection.h"

#include "../Vendor/imgui-docking/imgui.h"

#include "Component.h"
#include "Components/Transform.h"
#include "Components/MeshRenderer.h"
#include "Components/Camera.h"

void bluefir::editor::ComponentSection::Display(core::Component * c)
{
	switch  (c->type_)
	{
	case core::ComponentType::TRANSFORM:
		DisplayTransform(static_cast<core::Transform*>(c));
		break;
	case core::ComponentType::CAMERA:
		DisplayCamera(static_cast<core::Camera*>(c));
		break;
	case core::ComponentType::MESH_RENDERER:
		DisplayMeshRenderer(static_cast<core::MeshRenderer*>(c));
		break;
	default:
		break;
	}
}

void bluefir::editor::ComponentSection::DisplayTransform(core::Transform * c)
{
	if (ImGui::CollapsingHeader("Transform"))
	{
		float rot[3];
		c->GetRotationRaw(rot);

		ImGui::DragFloat3("Local Position", c->GetPositionRaw());
		if (ImGui::DragFloat3("Local Rotation", rot)) c->SetRotation(rot[0], rot[1], rot[2]);
		ImGui::DragFloat3("Local Scale", c->GetScaleRaw());
	}
}

void bluefir::editor::ComponentSection::DisplayMeshRenderer(core::MeshRenderer * c)
{
	if (ImGui::CollapsingHeader("MeshRenderer"))
	{
		ImGui::Text("Mesh ID: %i", c->mesh_ID_);
	}
}

void bluefir::editor::ComponentSection::DisplayCamera(core::Camera * c)
{
	if (ImGui::CollapsingHeader("Camera"))
	{
		float near = c->GetNearPlaneDistance();
		float far = c->GetFarPlaneDistance();
		float fov = c->GetFOV();

		if (ImGui::InputFloat("Near Plane Distance", &near))
			c->SetNearPlaneDistance(near);

		if (ImGui::InputFloat("Far Plane Distance", &far))
			c->SetFarPlaneDistance(far);

		if (ImGui::DragFloat("FOV", &fov, 1.0F, 30.0F, 90.0F))
			c->SetFOV(fov);
	}
}
