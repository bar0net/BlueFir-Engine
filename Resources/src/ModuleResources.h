#ifndef BF_CORE_MODULERESOURCEMANAGER
#define BF_CORE_MODULERESOURCEMANAGER

#include "Module.h"
#include <unordered_map>

// TODO: Maybe use something more sophisticated than random!
#include <random>

#define bluefir_resources bluefir::modules::ModuleResources::getInstance()
#define UID unsigned long long

namespace bluefir::resources
{
	class Resource;
}

namespace bluefir::modules
{
	class ModuleResources : public Module
	{
	public:
		static ModuleResources& getInstance() { static ModuleResources instance_; return instance_; }

		bool Init() override;
		bool CleanUp() override;

		UID Find(const char* file_in_assets) const;
		UID ImportFile(const char* file_in_assets, bool force = false);
		UID GenerateNewUID();
		inline const resources::Resource* Get(UID uid) const { auto it = resources_.find(uid);  return it != resources_.end() ? it->second : nullptr; }
		inline resources::Resource* Get(UID uid) { auto it = resources_.find(uid);  return it != resources_.end() ? it->second : nullptr; }
		resources::Resource* CreateNewResource(int type, UID force_uid = 0);

	private:
		ModuleResources() { generator.seed(std::random_device{}());	};
		~ModuleResources() {};
		
		void DeleteResource(UID uid);
		void DeleteResource(const char* exported_file);

	private:
		UID last_uid_ = 1;
		std::mt19937_64 generator;

		std::unordered_map < UID, resources::Resource*> resources_;
	};
}

#endif