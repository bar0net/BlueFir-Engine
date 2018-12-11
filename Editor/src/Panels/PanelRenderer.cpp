#include "PanelRenderer.h"

#include "ModuleRenderer.h"
#include "../../Vendor/imgui-docking/imgui.h"
#include "Mesh.h"

void bluefir::editor::PanelRenderer::Init()
{
}

void bluefir::editor::PanelRenderer::Draw()
{
	if (!enabled_) return;

	modules::ModuleRenderer* mr = &modules::ModuleRenderer::getInstance();
	ImGui::Begin(name_.c_str(), &enabled_);

	ImVec4 bgcolor(mr->clear_color_[0], mr->clear_color_[1], mr->clear_color_[2], mr->clear_color_[3]);

	bool open_bgcolor = ImGui::ColorButton("BGButton", bgcolor);
	ImGui::SameLine(); ImGui::Text("Background Color");
	if (open_bgcolor) ImGui::OpenPopup("ClearColorPicker");
	if (ImGui::BeginPopup("ClearColorPicker")) 
	{
		//if (ImGui::ColorPicker4("Clear Color", mr.clear_color_)) mr.UpdateClearColor();
		if (ImGui::ColorPicker4("Clear Color", &bgcolor.x)) 
			mr->SetClearColor(bgcolor.x, bgcolor.y, bgcolor.z, bgcolor.w);
		ImGui::EndPopup();
	}
	
	ImGui::Text("Window Size: %i x %i", mr->width_, mr->height_);
	ImGui::Text("[%f, %f, %f, %f]", mr->clear_color_[0], mr->clear_color_[1], mr->clear_color_[2], mr->clear_color_[3]);
	// TODO: Vsync selector
	
	if (ImGui::CollapsingHeader("Shaders"))
	{
		for (auto it = mr->shader_names_.begin(); it != mr->shader_names_.end(); ++it)
			ImGui::Text("[%i] %s", it->second, it->first.c_str());
	}

	if (ImGui::CollapsingHeader("Meshes"))
	{
		for (auto it = mr->meshes_.begin(); it != mr->meshes_.end(); ++it)
			ImGui::Text("[%i] %i vertices & %i indices", it->first, it->second->vertices_.size()/3, it->second->indices_.size());
	}

	ImGui::End();
}
