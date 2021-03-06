#include "ModuleScene.h"

#include "GameObject.h"
#include "Components/Camera.h"
#include "Components/Transform.h"
#include "Components/MeshRenderer.h"

#include "ModuleRenderer.h"
#include "ModelLoader.h"

#include "FileSystem.h"
#include "ModelLoader.h"

#include "ModuleResources.h"

bluefir::modules::ModuleScene::ModuleScene()
{
	//root_ = new core::GameObject();
	scene::scene_root = new bluefir::core::GameObject();
	root_ = scene::scene_root;
}

bluefir::modules::ModuleScene::~ModuleScene() { delete scene::scene_root; }

bool bluefir::modules::ModuleScene::Init()
{
	int shader_id = ModuleRenderer::getInstance().CreateShader("triangle.vs", "default.fs");

	ImportModel("Models/BakerHouse.fbx");
	/*
	int cube = CreateEmptyGameObject();
	gameObjects_[cube]->name = "Quad";
	gameObjects_[cube]->transform->SetPosition(0.0F, 0.0F, 0.0F);
	gameObjects_[cube]->transform->SetRotation(0, 0, 0);
	gameObjects_[cube]->transform->SetScale(0.5F, 0.5F, 1.0F);
	core::MeshRenderer* mr = gameObjects_[cube]->AddComponent<core::MeshRenderer>();
	int mesh_id = ModuleRenderer::getInstance().CreateMesh(graphics::ModelList::Cube);
	mr->SetMesh(mesh_id);
	mr->SetMaterial(shader_id);
	

	int tri = CreateEmptyGameObject();
	gameObjects_[tri]->name = "Triangle";
	gameObjects_[tri]->transform->SetPosition(0.0F, 5.0F, 0.0F);
	gameObjects_[tri]->transform->SetRotation(0, 0, 15.0F);
	gameObjects_[tri]->transform->SetScale(1.0F, 1.0F, 1.0F);
	gameObjects_[tri]->SetParent(gameObjects_[cube]);
	core::MeshRenderer* mr_t = gameObjects_[tri]->AddComponent<core::MeshRenderer>();
	int mesht_id = ModuleRenderer::getInstance().CreateMesh(graphics::ModelList::Triangle);
	mr_t->SetMesh(mesht_id);
	mr_t->SetMaterial(shader_id);
	*/

	//bluefir_resources.ImportFile("checkers.png", true);

	return true;
}

bluefir::modules::UpdateState bluefir::modules::ModuleScene::Update()
{
	//static float a = 0.0F;
	//a += 0.5F;
	//gameObjects_[1]->transform->SetRotation(0, 0, a);

	for (auto it = gameObjects_.begin(); it != gameObjects_.end(); ++it)
		it->second->PreUpdate();

	for (auto it = gameObjects_.begin(); it != gameObjects_.end(); ++it)
		it->second->Update();

	for (auto it = gameObjects_.begin(); it != gameObjects_.end(); ++it)
		it->second->PostUpdate();

	return UpdateState::Update_Continue;
}

bool bluefir::modules::ModuleScene::CleanUp()
{
	for (auto it = gameObjects_.begin(); it != gameObjects_.end(); ++it)
		delete it->second;
	gameObjects_.clear();
	//if (root_ != nullptr) delete root_;

	return true;
}

int bluefir::modules::ModuleScene::CreateEmptyGameObject(core::GameObject* parent)
{
	LOGINFO("Creating empty game object.");
	gameObjects_[gameObject_counter_] = new core::GameObject();
	if (parent) gameObjects_[gameObject_counter_]->SetParent(parent);
	else gameObjects_[gameObject_counter_]->SetParent(root_);
	++gameObject_counter_;

	return gameObject_counter_ - 1;
}

bool bluefir::modules::ModuleScene::ImportModel(const char * filename)
{

	std::vector<int> meshes;
	std::vector<int> materials;
	char* data = nullptr;

	int size = base::FileSystem::ImportAsset(filename, &data);
	core::ModelLoader::Load(data, size, meshes, materials);
	base::FileSystem::ReleaseFile(&data);

	int parent = CreateEmptyGameObject();
	gameObjects_[parent]->name = "GameObject";
	
	for (int mesh : meshes)
	{
		int game_object = CreateEmptyGameObject();
		gameObjects_[game_object]->name = std::string("Mesh_") + std::to_string(mesh);
		gameObjects_[game_object]->SetParent(gameObjects_[parent]);

		core::MeshRenderer* mr = gameObjects_[game_object]->AddComponent<core::MeshRenderer>();
		mr->SetMesh(mesh);
		mr->SetMaterial(0);
	}

	return false;
}
