#include "ComponentSection.h"

#include "../Vendor/imgui-docking/imgui.h"

#include "Component.h"
#include "Components/Transform.h"

void bluefir::editor::ComponentSection::Display(core::Component * c)
{
	switch  (c->type_)
	{
	case core::ComponentType::TRANSFORM:
		DisplayTransform(static_cast<core::Transform*>(c));
		break;
	case core::ComponentType::CAMERA:
		break;
	case core::ComponentType::MESH_RENDERER:
		break;
	default:
		break;
	}
}

void bluefir::editor::ComponentSection::DisplayTransform(core::Transform * c)
{
	float rot[3];
	c->GetRotationRaw(rot);

	ImGui::DragFloat3("Local Position", c->GetPositionRaw());
	if (ImGui::DragFloat3("Local Rotation", rot)) c->SetRotation(rot[0], rot[1], rot[2]);
	ImGui::DragFloat3("Local Scale", c->GetScaleRaw());
}
