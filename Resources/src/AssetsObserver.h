#ifndef BF_RESOURCES_ASSETSOBSERVER
#define BF_RESOURCES_ASSETSOBSERVER

#include <string>
#include <filesystem>
#include <vector>
#include <unordered_map>
#include <thread>
#include <mutex>

// TODO: Check why sometimes crashes when removing a file!

namespace bluefir::resources
{
	struct AssetsFile
	{
	public:
		AssetsFile(const char* path) : path(path), isDir(true), checked(true) {}
		AssetsFile(const char* path, unsigned int size, std::filesystem::file_time_type last_modified) : path(path), isDir(false), size(size), last_modified(last_modified), checked(true) {}
		virtual ~AssetsFile() { for (auto it = contents.begin(); it != contents.end(); ++it) delete it->second; contents.clear(); }

	public:
		std::string path;
		bool isDir = false;
		unsigned int size = 0;
		std::filesystem::file_time_type last_modified;
		std::unordered_map<std::string, AssetsFile*> contents;
		bool checked = true;
	};

	class AssetsObserver
	{
	public:
		AssetsObserver();
		virtual ~AssetsObserver();
		void Start() { run_thread = std::thread(&AssetsObserver::Run, this); }

		void GetAdditions(std::vector<std::string>** buffer);
		void GetRemovals(std::vector<std::string>** buffer);

	private:
		void Run();
		void DeleteContents(AssetsFile* file);
		void RegisterAddition(std::string file);
		void RegisterRemoval(std::string file);

	private:
		bool active = true;

		AssetsFile* root = nullptr;

		std::vector<std::string>* to_remove = nullptr;
		std::vector<std::string>* to_add = nullptr;
		std::thread run_thread;
		std::mutex mutex;
		bool mutex_violation = false;
	};
}
#endif // !BF_RESOURCES_ASSETSOBSERVER

