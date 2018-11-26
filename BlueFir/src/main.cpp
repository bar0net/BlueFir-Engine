#include "LogSystem.h"
#include "FileSystem.h"

#include "Graphics.h"
#include "Shader.h"

#include "Uniforms/UniformBlock.h"

#include <iostream>

#if (BF_DEBUG)
	#define _CRTDBG_MAP_ALLOC  
	#include <crtdbg.h> 
#else

#endif


int main(int argc, const char* argv[])
{
	bluefir::graphics::WindowData* data = bluefir::graphics::Graphics::StartWindow("x", 1280, 720);

	{
		LOGINFO("DEFAULT.VS");
		const char* v = bluefir::base::FileSystem::ReadFile("default.vs");

		LOGINFO("DEFAULT.FS");
		const char* f = bluefir::base::FileSystem::ReadFile("default.fs");

		LOGINFO("LOAD SHADER");
		bluefir::graphics::Graphics::CreateViewport(1280, 720, bluefir::graphics::Color(), 1.F);
		bluefir::graphics::Shader* s = new bluefir::graphics::Shader(v, f);

		bluefir::graphics::UniformBlock<char>* block = new bluefir::graphics::UniformBlock<char>(0,0,0,0, nullptr);
		block->Set(v);

		LOGINFO("DONE");
		delete block;
		delete s; s = nullptr;
		delete v; v = nullptr;
		delete f; f = nullptr;
		delete data;
	}


	#if (BF_DEBUG)
		bluefir::base::LogSystem::getInstance().Clear();
		_CrtDumpMemoryLeaks();
		std::cin.get();
	#endif

	return 0;
}