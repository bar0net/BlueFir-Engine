#include "ModuleScene.h"

#include "GameObject.h"
#include "Components/Camera.h"
#include "Components/Transform.h"

bluefir::modules::ModuleScene::~ModuleScene() {}

bool bluefir::modules::ModuleScene::Init()
{
	int go = CreateEmptyGameObject();
	gameObjects_[go]->AddComponent<core::Camera>();
	gameObjects_[go]->transform->SetPosition(0, 0, -10);

	return true;
}

bluefir::modules::UpdateState bluefir::modules::ModuleScene::Update()
{
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
