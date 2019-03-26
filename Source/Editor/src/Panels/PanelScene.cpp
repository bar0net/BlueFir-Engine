#include "PanelScene.h"

#include "../../Vendor/imgui-docking/imgui.h"

#include "ModuleScene.h"
#include "../ModuleEditor.h"

#include "GameObject.h"
#include "Component.h"
#include "Components/Transform.h"

#include "../ComponentSection.h"

#define BF_EDITOR_INDENTOFFSET 10

void bluefir::editor::PanelScene::Init()
{
}

void bluefir::editor::PanelScene::Draw()
{
	if (!enabled_) return; 

	ImGui::Begin(name_.c_str(), &enabled_);

	for (auto it = modules::ModuleScene::getInstance().root_->children_.begin(); it != modules::ModuleScene::getInstance().root_->children_.end(); ++it)
		DisplayGameObject(*it);

	ImGui::End();
}

void bluefir::editor::PanelScene::CleanUp()
{
}

void bluefir::editor::PanelScene::Inspect() const
{
	if (!selected_) return;

	for (auto it = selected_->components_.begin(); it != selected_->components_.end(); ++it)
	{
		for (auto jt = it->second.begin(); jt != it->second.end(); ++jt) 
		{
			core::Component* c = *jt;
			ComponentSection::Display(c);
		}
	}

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
	modules::ModuleEditor::getInstance().SetInspectContent(this);
}
