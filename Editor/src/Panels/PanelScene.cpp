#include "PanelScene.h"

#include "../../Vendor/imgui-docking/imgui.h"

#include "ModuleScene.h"
#include "GameObject.h"
#include "Components/Transform.h"

void bluefir::editor::PanelScene::Init()
{
}

void bluefir::editor::PanelScene::Draw()
{
	ImGui::Begin(name_.c_str(), &enabled_);

	for (auto it = modules::ModuleScene::getInstance().gameObjects_.begin(); it != modules::ModuleScene::getInstance().gameObjects_.end(); ++it)
	{
		if (it->second->parent_) continue;
		DisplayGameObject(it->second);
	}

	ImGui::End();
}

void bluefir::editor::PanelScene::CleanUp()
{
}

void bluefir::editor::PanelScene::DisplayGameObject(const core::GameObject* go, int level)
{
	// TODO: Have base gameobject append to a root object in Scene (?)

	if (go->children_.size() == 0)
	{
		bool enabled = false;
		if (selected_ == go) enabled = true;
		if (ImGui::Selectable(go->name.c_str(), enabled)) SetSelectedObject(go);
		return;
	}

	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
	if (selected_ == go) flags = ImGuiTreeNodeFlags_Selected;

	bool open = (ImGui::TreeNodeEx(go->name.c_str(), flags));
	if (ImGui::IsItemClicked()) SetSelectedObject(go);

	if (open)
	{
		for (auto it = go->children_.begin(); it != go->children_.end(); ++it)
			DisplayGameObject((*it), level + 1);
		ImGui::TreePop();
	}

}

void bluefir::editor::PanelScene::SetSelectedObject(const core::GameObject* go)
{
	selected_ = go;
}
