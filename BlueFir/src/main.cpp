#include "LogSystem.h"
#include "Chrono.h"
#include "FileSystem.h"

#include "ModuleRenderer.h"
#include "Shader.h"

#include "Mesh.h"

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

	const char* vShader = bluefir::base::FileSystem::ReadFile("triangle.vs");
	const char* fShader = bluefir::base::FileSystem::ReadFile("default.fs");
	bluefir::graphics::Shader* shader = new bluefir::graphics::Shader(vShader, fShader);

	bluefir::graphics::Mesh* mesh = bluefir::graphics::StandardModels::Triangle();
	while (c.Pause() < 5000)
	{
		renderer->PreUpdate();
		renderer->Draw(*mesh, *shader);

		renderer->Render();
	}

	renderer->CleanUp();
	c.Stop();
	delete shader;

	#if (BF_DEBUG)
	LOGINFO("End of main.");
		bluefir::base::LogSystem::getInstance().Clear();
		_CrtDumpMemoryLeaks();
		std::cin.get();
	#endif

	return 0;
}