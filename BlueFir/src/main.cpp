#include "LogSystem.h"
#include "FileSystem.h"
#include "Chrono.h"
#include "MovingArray.h"

#include <iostream>

#if (BF_DEBUG)
	#define _CRTDBG_MAP_ALLOC  
	#include <crtdbg.h> 
#else

#endif

int main(int argc, const char* argv[])
{
	{
		bluefir::base::Chrono chrono;
		bluefir::base::uChrono uchrono;

		chrono.Start();
		uchrono.Start();

		LOGINFO("Logging test");

		for (size_t i = 0; i < 10; i++)
		{
			const char* data = bluefir::base::FileSystem::ReadFile("test.txt");
			LOGINFO("Contents: %s", data);
			delete[] data;
		}
		LOGINFO("uChrono: %f", uchrono.Pause());
		LOGINFO("Chrono: %i", chrono.Pause());

		bluefir::base::MovingArray<int> m(20, 0);
		for (int i = 0; i < 25; ++i)
		{
			m.Push(i);
			for (int j = 0; j < 20; j++)
			{
				std::cout << m[j] << " ";
			}
			std::cout << std::endl;
		}

		LOGINFO("uChrono: %fms", uchrono.Stop());
		LOGINFO("Chrono: %ims", chrono.Stop());
	}

	#if (BF_DEBUG)
		bluefir::base::LogSystem::getInstance().Clear();
		_CrtDumpMemoryLeaks();
		std::cin.get();
	#endif
}