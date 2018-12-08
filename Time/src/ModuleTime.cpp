#include "ModuleTime.h"

bool bluefir::modules::ModuleTime::Init()
{
	LOGINFO("Initializing timer module.");
	chrono.Start(); 
	return true;
}