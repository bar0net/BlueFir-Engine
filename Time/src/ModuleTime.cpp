#include "ModuleTime.h"

bool bluefir::modules::ModuleTime::Init()
{
	LOGINFO("Initializing timer module.");
	chrono.Start(); 
	return true;
}

bluefir::modules::UpdateState bluefir::modules::ModuleTime::PreUpdate()
{ 
	delta_time_ = chrono.Pause() - real_last_;
	real_last_ = chrono.Pause(); 

	if (active_)
	{
		running_time_ += time_scale_ * (float)delta_time_;
		unscaled_running_time_ += (float)delta_time_;
	}
	return UpdateState::Update_Continue; 
}