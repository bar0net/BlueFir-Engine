#include "LogSystem.h"
#include "Chrono.h"

#include "ModuleRenderer.h"

#include <iostream>

#if (BF_DEBUG)
	#define _CRTDBG_MAP_ALLOC  
	#include <crtdbg.h> 
#else

#endif


int main(int argc, const char* argv[])
{
	bluefir::modules::ModuleRenderer* renderer = new bluefir::modules::ModuleRenderer();
	bluefir::base::Chrono c;
	c.Start();

	renderer->Init();

	while (c.Pause() < 20000)
	{
		renderer->PreUpdate();
		

		renderer->Render();
	}

	renderer->CleanUp();
	c.Stop();

	#if (BF_DEBUG)
	LOGINFO("End of main.");
		bluefir::base::LogSystem::getInstance().Clear();
		_CrtDumpMemoryLeaks();
		std::cin.get();
	#endif

	return 0;
}