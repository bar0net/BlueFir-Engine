#include "FileSystem.h"

#include "LogSystem.h"

// TODO: Migrate to PhysFX?
#include <stdio.h>
#include <stdlib.h>


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

bool bluefir::base::FileSystem::ExportFile(const char * filename, const char * data, unsigned int size)
{
	ASSERT(filename && data);

	LOGINFO("Exporting file: %s", filename);
	FILE* file = nullptr;
	fopen_s(&file, filename, "wb");

	if (file)
	{
		std::fwrite(data, sizeof(char), size, file);
		fclose(file);
		return true;
	}
	else
	{
		LOGERROR("Could not export file: %s", filename);
		fclose(file);
		return false;
	}
	
	return false;
}

int bluefir::base::FileSystem::ImportFile(const char* filename, char** data)
{
	ASSERT(filename);
	int size = 0;

	LOGINFO("Read file: %s", filename);
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

const char * bluefir::base::FileSystem::GetFileExtension(const char * path)
{
	ASSERT(path);

	const char* last_dot = nullptr;
	while (++path != NULL && last_dot == nullptr) 
	{
		char x = *path;

		if ( x == '.')
		{
			last_dot = path + 1;
		}
	}

	return last_dot;
}

std::string bluefir::base::FileSystem::GetFileMetaPath(UID uid, bool force_create)
{
	// TODO: Check this!
	std::string str_uid = std::to_string(uid);
	std::string path = std::string(BF_FILESYSTEM_CONFIGDIR) + std::string("/") + str_uid.substr(0, 2);

	if (force_create || !std::filesystem::exists(path.c_str()))
		std::filesystem::create_directory(path.c_str());

	path += std::string("/") + str_uid + std::string(".meta");
	return path;
}

std::string bluefir::base::FileSystem::GetFileMetaPath(const char * uid, bool force_create)
{
	// TODO: Check this!
	std::string str_uid = std::string(uid);
	std::string path = std::string(BF_FILESYSTEM_CONFIGDIR) + std::string("/") + str_uid.substr(0, 2);

	if (force_create && !std::filesystem::exists(path.c_str()))
		std::filesystem::create_directory(path.c_str());

	path += std::string("/") + str_uid + std::string(".meta");
	return path;
}


std::vector<std::string> bluefir::base::FileSystem::ReadDirectory(const char* path)
{
	ASSERT(path);
	std::vector<std::string> directory;

	if (!std::filesystem::exists(path))
	{
		LOGERROR("Trying to read %s but it doesn't exist.", path);
		return std::vector<std::string>();
	}

	for (const auto &entry : std::filesystem::directory_iterator(path))
	{
		std::string s = entry.path().string();

		/*bool b = std::string("a\\b") == std::string("a/b");

		size_t it = s.find("\\");
		while (it != s.npos)
		{
			s.replace(it,1,"/");
			size_t it = s.find_first_of("\\");
		}*/
		std::replace(s.begin(), s.end(), '\\', '/');

		directory.emplace_back(s);
	}

	return directory;
}

std::vector<std::string> bluefir::base::FileSystem::GetFilesInDir(const char * directory, bool include_directories)
{
	ASSERT(directory);
	std::vector<std::string> files;

	if (!ExistsDir(directory))
	{
		LOGERROR("Could not acces %s.", directory);
		return files;
	}

	std::vector<std::string> explore = ReadDirectory(directory);

	while (!explore.empty())
	{
		std::string current = explore.front();
		if ( IsDir(current.c_str()) )
		{
			if (include_directories) files.push_back(current);
			std::vector<std::string> new_files = ReadDirectory(current.c_str());
			explore.insert(explore.begin()+1, new_files.begin(), new_files.end());
		}
		else
		{
			files.push_back(current);
		}
		explore.erase(explore.begin());
	}

	return files;
}
