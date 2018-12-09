#include "ModuleScene.h"

#include "GameObject.h"
#include "Components/Camera.h"
#include "Components/Transform.h"
#include "ModuleRenderer.h"
#include "Components/MeshRenderer.h"


bluefir::modules::ModuleScene::~ModuleScene() {}

bool bluefir::modules::ModuleScene::Init()
{
	int cam = CreateEmptyGameObject();
	gameObjects_[cam]->name = "Cam";
	gameObjects_[cam]->AddComponent<core::Camera>();
	gameObjects_[cam]->transform->SetPosition(0, 0.0F, 10.0F);
	gameObjects_[cam]->transform->SetRotation(0, 0.0F, 0);

	int cube = CreateEmptyGameObject();
	gameObjects_[cube]->name = "Quad";
	gameObjects_[cube]->transform->SetPosition(0.0F, 0.0F, 0.0F);
	gameObjects_[cube]->transform->SetRotation(0, 0, 0);
	gameObjects_[cube]->transform->SetScale(0.5F, 0.5F, 1.0F);
	core::MeshRenderer* mr = gameObjects_[cube]->AddComponent<core::MeshRenderer>();
	int mesh_id = ModuleRenderer::getInstance().CreateMesh(graphics::ModelList::Quad);
	mr->SetMesh(mesh_id);
	int shader_id = ModuleRenderer::getInstance().CreateShader("triangle.vs", "default.fs");
	mr->SetMaterial(shader_id);

	int tri = CreateEmptyGameObject(gameObjects_[cube]);
	gameObjects_[tri]->name = "Triangle";
	gameObjects_[tri]->transform->SetPosition(0.0F, 2.0F, 0.0F);
	gameObjects_[tri]->transform->SetRotation(0, 0, 15.0F);
	gameObjects_[tri]->transform->SetScale(1.0F, 1.0F, 1.0F);
	core::MeshRenderer* mr_t = gameObjects_[tri]->AddComponent<core::MeshRenderer>();
	int mesht_id = ModuleRenderer::getInstance().CreateMesh(graphics::ModelList::Triangle);
	mr_t->SetMesh(mesht_id);
	mr_t->SetMaterial(shader_id);

	return true;
}

bluefir::modules::UpdateState bluefir::modules::ModuleScene::Update()
{
	static float a = 0.0F;
	a += 0.5F;
	gameObjects_[1]->transform->SetRotation(0, 0, a);

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

	return true;
}

int bluefir::modules::ModuleScene::CreateEmptyGameObject(core::GameObject* parent)
{
	LOGINFO("Creating empty game object.");
	gameObjects_[gameObject_counter_] = new core::GameObject();
	if (parent) gameObjects_[gameObject_counter_]->SetParent(parent);
	++gameObject_counter_;

	return gameObject_counter_ - 1;
}
