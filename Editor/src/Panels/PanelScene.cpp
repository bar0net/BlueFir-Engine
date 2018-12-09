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

void bluefir::editor::PanelScene::DisplayGameObject(const core::GameObject* go, int level) const
{
	// TODO: Have base gameobject append to a root object in Scene (?)

	std::string s = "";
	for (int i = 0; i < level; ++i) s.append("  ");
	ImGui::Text("%s%s", s.c_str(), go->name.c_str());

	for (auto it = go->children_.begin(); it != go->children_.end(); ++it)
		DisplayGameObject((*it), level + 1);
}
