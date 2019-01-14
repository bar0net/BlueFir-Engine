#include "FileSystem.h"

#include "LogSystem.h"

// TODO: Migrate to PhysFX
#include <stdio.h>
#include <stdlib.h>

#include "BaseMacros.h"

const char* bluefir::base::FileSystem::ReadFile(const char* filename)
{
	ASSERT(filename);

	LOGINFO("Read file: %s", filename);
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

int bluefir::base::FileSystem::ImportAsset(const char * filename, char** data)
{
	std::string s = BF_FILESYSTEM_ASSETSDIR + std::string("/") + filename;
	return ImportFile(s.c_str(), data);
}

int bluefir::base::FileSystem::ImportFile(const char* filename, char** data)
{
	ASSERT(filename);
	int size = 0;

	LOGINFO("Read file: %s", filename);
	/*if (*data != nullptr) 
	{ 
		delete[] *data; *data = nullptr; 
	}*/
	FILE* file = nullptr;
	fopen_s(&file, filename, "rb");

	if (file)
	{
		fseek(file, 0, SEEK_END);
		size = ftell(file);
		rewind(file);
		*data = new char[size + 1];

		fread(*data, 1, size, file);
		(*data)[size] = 0;

		fclose(file);
	}

	return size;
}

void bluefir::base::FileSystem::ReleaseFile(char ** data)
{
	if (*data) 
	{ 
		delete[] *data; *data = nullptr; 
	}
}

void bluefir::base::FileSystem::ReleaseFile(const char ** data)
{
	if (*data)
	{
		delete[] * data; *data = nullptr;
	}
}

std::vector<bluefir::base::File> bluefir::base::FileSystem::ReadDirectory(const char* path)
{
	ASSERT(path);
	std::vector<bluefir::base::File> directory;

	// base::File
	for (const auto &entry : std::filesystem::directory_iterator(path))
	{
		/*
		directory.emplace_back(
			entry.path().string().substr(std::strlen(path) + 1),
			entry.path().string(),
			entry.last_write_time(),
			entry.file_size()
		);
		*/
	}

	return directory;
}
