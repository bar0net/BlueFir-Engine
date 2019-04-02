#include "PanelResourcePreview.h"

#include "imgui.h"

#include "ModuleResources.h"

#include "Resource.h"
#include "Resource/ResourceTexture.h"

void bluefir::editor::PanelResourcePreview::Draw()
{
	if (!enabled_)
	{
		if (resource_loaded) resource_loaded = !resource->UnloadFromMemory();
		return;
	}

	ImGui::Begin(name_.c_str(), &enabled_);
	if (!resource) { ImGui::End(); return; }
	if (!resource_loaded) resource_loaded = resource->LoadInMemory();
	if (!resource_loaded) Release(); // There has been an error loading the resource!

	switch (resource->GetType())
	{
	case resources::Type::TEXTURE:   DrawTexture(); break;
	default:
		break;
	}

	ImGui::End();
}

void bluefir::editor::PanelResourcePreview::Set(unsigned long long int uid)
{
	resource = bluefir_resources.Get(uid);
	if (!resource) return; 

	resource_loaded = resource->LoadInMemory();

	switch (resource->GetType())
	{
	case resources::Type::TEXTURE:
		break;
	default:
		break;
	}
}

void bluefir::editor::PanelResourcePreview::Release()
{
	resource->UnloadFromMemory();
	resource = nullptr;
	resource_loaded = false;
}

void bluefir::editor::PanelResourcePreview::DrawTexture()
{
	resources::ResourceTexture* texture = (resources::ResourceTexture*)resource;

	ImVec2 size = ImGui::GetContentRegionAvail();
	if (size.y / size.x <= texture->height / texture->width)
		size.x = size.y * texture->width / texture->height;
	else
		size.y = size.x * texture->height / texture->width;

	ImGui::Image((ImTextureID)texture->gpu_id, size);
}
