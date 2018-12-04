#include "BlueFir.h"
#include "LogSystem.h"

#if (BF_DEBUG)
	#include <iostream>
	#define _CRTDBG_MAP_ALLOC  
	#include <crtdbg.h> 
#endif

enum class AppStatus
{
	None = 0,
	Start,
	Update,
	End,
	Exit
};

bluefir::BlueFir* App = nullptr;
int main(int argc, const char* argv[])
{
	LOGINFO("Begin Application.");
	App = new bluefir::BlueFir();

	AppStatus status = AppStatus::Start;

	while (status != AppStatus::Exit)
	{
		switch (status)
		{
		case AppStatus::Start:
			LOGINFO("Application Start.");
			if (App->Start())
			{
				status = AppStatus::Update;
				LOGINFO("Application Main Loop.");
			}
			break;

		case AppStatus::Update:
			if (!App->Update()) status = AppStatus::End;
			break;

		case AppStatus::End:
			LOGINFO("Application End.");
			App->End();
			status = AppStatus::Exit;
			break;

		default:
			status = AppStatus::Exit;
			break;
		}
	}

	LOGINFO("Application Clear.");
	delete App;

	#if (BF_DEBUG)
		LOGINFO("End of main.");
		bluefir::base::LogSystem::getInstance().Clear();
		_CrtDumpMemoryLeaks();
		std::cin.get();
	#endif

	return 0;
}