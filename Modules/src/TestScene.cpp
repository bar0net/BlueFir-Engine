#include "TestScene.h"

#include "ModelManager.h"

bluefir::modules::UpdateState bluefir::modules::TestScene::Update()
{
	this->cube = graphics::ModelManager::Cube();



	return UpdateState::Update_Continue;
}

bool bluefir::modules::TestScene::CleanUp()
{
	delete cube;
	return true;
}
