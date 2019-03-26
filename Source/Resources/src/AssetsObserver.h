#ifndef BF_RESOURCES_ASSETSOBSERVER
#define BF_RESOURCES_ASSETSOBSERVER

#include <string>
#include <vector>
#include <unordered_map>
#include <thread>
#include <mutex>

#include "FileSystem.h"

namespace bluefir::resources
{
	struct AssetsFile
	{
	public:
		AssetsFile(const char* path) : path(path), checked(false) { last_modified = base::FileSystem::FileModifiedTime(path); }
		virtual ~AssetsFile() {}

		inline bool HasChanged() const { return last_modified != base::FileSystem::FileModifiedTime(path.c_str()); }

	public:
		std::string path;
		std::filesystem::file_time_type last_modified;
		bool checked = false;
	};

	class AssetsObserver
	{
	public:
		AssetsObserver();
		virtual ~AssetsObserver();
		void Start();

		void GetAdditions(std::vector<std::string>** buffer);
		void GetRemovals(std::vector<std::string>** buffer);

		std::vector<std::string> GetAssetList();

	private:
		void Run();
		void RegisterAddition(std::string file);
		inline void RegisterModification(std::string file) { RegisterRemoval(file); RegisterAddition(file); }
		void RegisterRemoval(std::string file);

		void AddAsset(const char* file);
		void UpdateAssetList();

	private:
		bool active = true;

		AssetsFile* root = nullptr;

		std::unordered_map<std::string,AssetsFile*> registered_assets;
		std::vector<std::string> asset_list;

		std::vector<std::string>* to_remove = nullptr;
		std::vector<std::string>* to_add = nullptr;
		std::thread run_thread;
		std::mutex mutex;
		bool mutex_violation = false;
	};
}
#endif // !BF_RESOURCES_ASSETSOBSERVER

