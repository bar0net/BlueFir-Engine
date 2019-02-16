#ifndef BLUEFIR_BASE_FILESYS_H
#define BLUEFIR_BASE_FILESYS_H

#include <filesystem>
#include <vector>

#define BF_FILESYSTEM_ASSETSDIR "Assets"
#define BF_FILESYSTEM_LIBRARYDIR "Library"

namespace bluefir::base
{
	// TODO: Check if File is needed
	struct File
	{
		File() {}
		File(const char* name, const char* path) : name_(name)
		{
			std::filesystem::directory_entry entry(path);
			path_ = entry.path().string();
			last_write_ = entry.last_write_time();
			size_ = entry.file_size();
			is_folder_ = entry.is_directory();
		}

		bool HasChanged() 
		{ 
			std::filesystem::directory_entry entry(path_);
			return entry.file_size() != size_ || entry.last_write_time() != last_write_;
		}

		bool is_folder_ = false;
		unsigned int size_ = 0U;
		std::string name_;
		std::string path_;
		const File* parent_ = nullptr;

		std::filesystem::file_time_type last_write_;
	};

	class FileSystem
	{
	public:
		static const char* ReadFile(const char* filename);
		static int ImportFile(const char* filename, char** data);
		static int ImportAsset(const char* filename, char** data);
		static bool ExportFile(const char* filename, const char* data, unsigned int size);

		static void ReleaseFile(char** data);
		static void ReleaseFile(const char** data);

		static const char* GetFileExtension(const char* path);

		static std::vector<std::string> ReadDirectory(const char* path);
		static inline bool IsDir(const char* path)		{ return std::filesystem::is_directory(path); }
		static inline bool ExistsDir(const char* path)	{ return std::filesystem::exists(path); }
		static inline bool CreateDir(const char* path)	{ return std::filesystem::create_directory(path); }
	private:
		FileSystem() = delete;
	};
}

#endif //!BLUEFIR_BASE_FILESYS_H