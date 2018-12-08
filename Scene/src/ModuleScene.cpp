#include "ModuleScene.h"


bluefir::modules::ModuleScene::~ModuleScene()
{
}

bool bluefir::modules::ModuleScene::Init()
{
	return true;
}

bluefir::modules::UpdateState bluefir::modules::ModuleScene::Update()
{
	return UpdateState::Update_Continue;
}

bool bluefir::modules::ModuleScene::CleanUp()
{
	return true;
}

int bluefir::modules::ModuleScene::CreateEmptyGameObject(const core::GameObject* parent)
{
	return 0;
}
