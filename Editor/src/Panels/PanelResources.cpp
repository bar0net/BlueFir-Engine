#include "PanelResources.h"

#include "../../Vendor/imgui-docking/imgui.h"

#include "ModuleResources.h"
#include "Resource.h"

void bluefir::editor::PanelResources::Init()
{
}

void bluefir::editor::PanelResources::Draw()
{
	if (!enabled_) return;
	ImGui::Begin(name_.c_str(), &enabled_);

	for (auto it = bluefir_resources.resources_.begin(); it != bluefir_resources.resources_.end(); ++it)
	{
		const char* resource_type = nullptr;
		switch (it->second->GetType())
		{
		case bluefir::resources::Type::TEXTURE:
			resource_type = "Texture";
			break;

		case bluefir::resources::Type::MESH:
			resource_type = "Mesh";
			break;

		case bluefir::resources::Type::UNKNOWN:
			resource_type = "None";
			break;

		default:
			resource_type = "None";
			break;
		}

		if (it->second->IsLoadedToMemory())
			ImGui::TextColored(ImVec4(0.2f, 1.0f, 0.2f, 1.0f), "[%s - %d] %s | %d", resource_type, it->second->GetUID(), it->second->GetFile(), it->second->Count());
		else
			ImGui::Text("[%s - %s] %s | %d", resource_type, std::to_string(it->second->GetUID()).c_str(), it->second->GetFile(), it->second->Count());
	}

	ImGui::End();
}
