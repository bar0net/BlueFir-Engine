#include "PanelResources.h"

#include "../../Vendor/imgui-docking/imgui.h"

#include "AssetsObserver.h"
#include "ModuleResources.h"
#include "Resource.h"

#include "../ModuleEditor.h"
#include "PanelResourcePreview.h"

#include <string>
#include <vector>
#include <stack>

void bluefir::editor::PanelResources::Init()
{
}

void bluefir::editor::PanelResources::Draw()
{
	if (!enabled_) return;
	ImGui::Begin(name_.c_str(), &enabled_);

	std::vector<std::string> asset_list = bluefir_resources.observer->GetAssetList();

	if (ImGui::TreeNode("Assets"))
	{
		std::stack<std::string> asset_container;
		std::stack<bool> node_open;
		asset_container.push(BF_FILESYSTEM_ASSETSDIR);
		node_open.push(true);

		for (std::string it : asset_list)
		{
			while (!asset_container.empty() && it.find(asset_container.top()) == it.npos)
			{
				if (asset_container.empty()) break;
				asset_container.pop();
				if (node_open.top()) ImGui::TreePop();
				node_open.pop();
			}

			size_t length = asset_container.top().length();
			std::string name = it.substr(length+1, it.npos);

			if (base::FileSystem::IsDir(it.c_str())) 
			{
				asset_container.push(it);
				node_open.push(ImGui::TreeNode(name.c_str()));
			}
			else
			{
				if (node_open.top())
				{
					bool selected = (it == selected_asset);
					if (ImGui::Selectable(name.c_str(), &selected))
					{
						if (selected_uid != 0) ((PanelResourcePreview*)bluefir_editor.resource_preview_)->Release();
						selected_asset = it;
						selected_uid = bluefir_resources.Find(selected_asset.c_str());
						((PanelResourcePreview*)bluefir_editor.resource_preview_)->Set(selected_uid);
					}
				}
				//if (ImGui::TreeNode(name.c_str())) ImGui::TreePop();
			}
		}

		while (!node_open.empty()) 
		{ 
			if (node_open.top()) ImGui::TreePop();
			node_open.pop();
		}
	}


	ImGui::Separator();

	ImGui::Text("Selected Resource:");
	UID uid = bluefir_resources.Find(selected_asset.c_str());

	if (uid != 0)
	{
		const resources::Resource* resource = bluefir_resources.Get(uid);
		ImGui::Text("UID: %s\nFile: %s\nType: %d\nInstances: %d", std::to_string(resource->GetUID()).c_str(), resource->GetFile(), (unsigned)resource->GetType(), resource->Count());
	}

	ImGui::End();
}
