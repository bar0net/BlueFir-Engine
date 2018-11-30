#include "TestScene.h"

#include "Mesh.h"

bluefir::modules::UpdateState bluefir::modules::TestScene::Update()
{
	this->cube = graphics::StandardModels::Cube();



	return UpdateState::Update_Continue;
}

bool bluefir::modules::TestScene::CleanUp()
{
	delete cube;
	return true;
}
