#include "PanelTexture.h"

#include "../../Vendor/imgui-docking/imgui.h"
#include "ModuleTexture.h"
#include "Buffer/TextureBuffer.h"

#define BF_TEXTURES modules::ModuleTexture::getInstance()

void bluefir::editor::PanelTexture::Draw()
{
	ImGui::Begin(name_.c_str(), &enabled_);

	for (auto it = BF_TEXTURES.texture_names_.begin(); it != BF_TEXTURES.texture_names_.end(); ++it)
	{
		ImGui::Text("[%i]", it->second); ImGui::SameLine();
		ImGui::Image((ImTextureID)(it->second), ImVec2(50,50)); ImGui::SameLine();
		ImGui::Text("%s", it->first.c_str());
	}

	ImGui::End();
}
