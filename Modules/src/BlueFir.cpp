#include "BlueFir.h"

#include "Module.h"
#include "ModuleInput.h"
#include "ModuleRenderer.h"
#include "ModuleTime.h"

bluefir::BlueFir::BlueFir()
{
	modules_.push_back(renderer = new modules::ModuleRenderer());
	modules_.push_back(input = new modules::ModuleInput());
	modules_.push_back(time = new modules::ModuleTime());
}

bluefir::BlueFir::~BlueFir()
{
	modules_.clear();
	delete input;		input = nullptr;
	delete renderer;	renderer = nullptr;
	delete time;		time = nullptr;
}

bool bluefir::BlueFir::Start()
{
	bool ret = true;

	for (auto it = modules_.begin(); it != modules_.end() && ret; ++it)
		ret = (*it)->Init();

	for (auto it = modules_.begin(); it != modules_.end() && ret; ++it)
		ret = (*it)->Start();

	return ret;
}

bool bluefir::BlueFir::Update()
{
	modules::UpdateState ret = modules::UpdateState::Update_Continue;

	for (auto it = modules_.begin(); it != modules_.end() && ret == modules::UpdateState::Update_Continue; ++it)
		ret = (*it)->PreUpdate();

	for (auto it = modules_.begin(); it != modules_.end() && ret == modules::UpdateState::Update_Continue; ++it)
		ret = (*it)->Update();

	for (auto it = modules_.begin(); it != modules_.end() && ret == modules::UpdateState::Update_Continue; ++it)
		ret = (*it)->PostUpdate();

	if (ret == modules::UpdateState::Update_Continue) ret = renderer->Render();

	return ret == modules::UpdateState::Update_Continue;
}

bool bluefir::BlueFir::End()
{
	bool ret = true;

	for (auto it = modules_.begin(); it != modules_.end() && ret; ++it)
		ret = (*it)->End();

	for (auto it = modules_.rbegin(); it != modules_.rend() && ret; ++it)
		ret = (*it)->CleanUp();

	return ret;
}
