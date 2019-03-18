#ifndef BLUEFIR_BASE_FILESYS_H
#define BLUEFIR_BASE_FILESYS_H

#include <filesystem>
#include <vector>

#define BF_FILESYSTEM_ASSETSDIR "Assets"
#define BF_FILESYSTEM_LIBRARYDIR "Library"
#define BF_FILESYSTEM_CONFIGDIR "Config"

namespace bluefir::base
{
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
		static std::string GetFileMetaPath(long long int uid, bool force_create = false);
		static std::string GetFileMetaPath(const char* uid, bool force_create = false);

		static std::vector<std::string> ReadDirectory(const char* path);
		static inline bool IsDir(const char* path)		{ return std::filesystem::is_directory(path); }
		static inline bool ExistsDir(const char* path)	{ return std::filesystem::exists(path); }
		static inline bool CreateDir(const char* path)	{ return std::filesystem::create_directory(path); }
		static inline void DeleteFile(const char* path) { if (std::filesystem::exists(path)) std::filesystem::remove(path); }
		static inline unsigned int FileSize(const char* path) { return (std::filesystem::exists(path)) ? (unsigned int)std::filesystem::file_size(path) : 0U; }
		static inline std::filesystem::file_time_type FileModifiedTime(const char* path) { return (std::filesystem::exists(path)) ? std::filesystem::last_write_time(path) : std::filesystem::file_time_type(); }

	private:
		FileSystem() = delete;
	};
}

#endif //!BLUEFIR_BASE_FILESYS_H