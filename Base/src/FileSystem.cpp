#include "FileSystem.h"

#if (BF_DEBUG)
	#include <assert.h>
	#define ASSERT(x) assert(x)
#else
	#define ASSERT(X)
#endif

#include <stdio.h>
#include <stdlib.h>

const char* bluefir::base::FileSystem::ReadFile(const char* filename)
{
	ASSERT(filename);

	char* data = nullptr;
	FILE* file = nullptr;
	fopen_s(&file, filename, "rb");

	if (file)
	{
		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		rewind(file);
		data = new char[size + 1];

		fread(data, 1, size, file);
		data[size] = 0;

		fclose(file);
	}

	return data;
}
