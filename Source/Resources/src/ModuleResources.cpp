#include "ModuleResources.h"
#include "BaseMacros.h"

#include <vector>

#include "json.h"
#include "FileSystem.h"
#include "Importer.h"

#include "Resource/ResourceTexture.h"
#include "AssetsObserver.h"

#define IS_IN_ASSETS(x) base::FileSystem::ExistsDir(x)

bool bluefir::modules::ModuleResources::Init()
{
	LOGINFO("Initializing Resource Module.");
	observer = new resources::AssetsObserver();

	// Create directories if they don't exist 
	if (!base::FileSystem::ExistsDir(BF_FILESYSTEM_ASSETSDIR))  base::FileSystem::CreateDir(BF_FILESYSTEM_ASSETSDIR);
	if (!base::FileSystem::ExistsDir(BF_FILESYSTEM_LIBRARYDIR)) base::FileSystem::CreateDir(BF_FILESYSTEM_LIBRARYDIR);
	if (!base::FileSystem::ExistsDir(BF_FILESYSTEM_CONFIGDIR))	base::FileSystem::CreateDir(BF_FILESYSTEM_CONFIGDIR);

	// Retrieve the list of files in each directory
	std::vector<std::string> assets  = base::FileSystem::GetFilesInDir(BF_FILESYSTEM_ASSETSDIR);
	std::vector<std::string> meta    = base::FileSystem::GetFilesInDir(BF_FILESYSTEM_CONFIGDIR);
	std::vector<std::string> library = base::FileSystem::GetFilesInDir(BF_FILESYSTEM_LIBRARYDIR);

	// Load meta Files
	for (auto it : meta) LoadMetaFile(it.c_str());

	// Erase unregistered library files
	for (auto it = resources_.begin(); it != resources_.end(); ++it)
	{
		auto jt = library.end();
		while (jt > library.begin())
		{
			--jt;
			if (std::strcmp(it->second->GetExportedFile(), jt->c_str()) == 0) {jt = library.erase(jt); break;}
		}
	}
	for (auto jt : library) base::FileSystem::DeleteFile(jt.c_str());

	// Add new assets
	for (auto it = resources_.begin(); it != resources_.end(); ++it)
	{
		auto jt = assets.end();
		while (jt > assets.begin())
		{
			--jt;
			if (std::strcmp(it->second->GetExportedFile(), jt->c_str()) == 0) {jt = assets.erase(jt); break;}
		}
	}
	for (auto jt : assets) ImportFile(jt.c_str());

	observer->Start();
	return true;
}

bool bluefir::modules::ModuleResources::CleanUp()
{
	LOGINFO("Closing Resource Module.");

	for (auto it = resources_.begin(); it != resources_.end(); ++it)
		delete it->second;
	resources_.clear();

	delete observer;
	return true;
}

bluefir::modules::UpdateState bluefir::modules::ModuleResources::PreUpdate()
{
	std::vector<std::string>* buffer = nullptr;
	
	observer->GetRemovals(&buffer);
	if (buffer)
	{
		for (auto it = buffer->begin(); it != buffer->end(); ++it)
		{
			UID uid = Find(it->c_str());
			if (uid != 0) DeleteResource(uid);
		}
		delete buffer; buffer = nullptr;
	}

	observer->GetAdditions(&buffer);
	if (buffer)
	{
		for (auto it = buffer->begin(); it != buffer->end(); ++it)
		{
			ImportFile(it->c_str(), observer_initialized);
		}
		observer_initialized = true;
		delete buffer; buffer = nullptr;
	}

	return UpdateState::Update_Continue;
}

UID bluefir::modules::ModuleResources::Find(const char * file_in_assets) const
{
	ASSERT(file_in_assets);

	for (auto it = resources_.begin(); it != resources_.end(); ++it)
	{
		if (it->second->CheckFile(file_in_assets)) return it->second->GetUID();
	}

	return 0;
}

UID bluefir::modules::ModuleResources::ImportFile(const char * file_in_assets, bool force)
{
	ASSERT(file_in_assets);

	//std::string path = BF_FILESYSTEM_ASSETSDIR + std::string("/") + file_in_assets;
	std::string path = file_in_assets;
	UID uid = Find(path.c_str());
	resources::Resource* resource = nullptr;

	if (force || uid == 0)
	{
		if (force && uid != 0) DeleteResource(uid);
		if (uid == 0) uid = GenerateNewUID();

		std::string extension = base::FileSystem::GetFileExtension(path.c_str());

		if (extension == "png")
		{
			resource = resources::Importer::Texture(file_in_assets, uid);
		}


		if (resource == nullptr)
		{
			LOGERROR("An error has occurred while importing %s.", path.c_str());
			return 0U;
		}
		else
		{
			LOGINFO("Successfully imported %s.", path.c_str());
			resource->Save();
			resources_[uid] = resource;
		}
	}
	else
	{
		LOGDEBUG("Using previously imported %s.", path.c_str());
	}

	return uid;
}

UID bluefir::modules::ModuleResources::GenerateNewUID()
{
	last_uid_ = generator();
	while (resources_.find(last_uid_) != resources_.end()) last_uid_ = generator();

	return last_uid_;
}

bluefir::resources::Resource * bluefir::modules::ModuleResources::CreateNewResource(int type, UID force_uid)
{
	return nullptr;
}

void bluefir::modules::ModuleResources::DeleteResource(UID uid)
{
	std::string file = resources_[uid]->GetExportedFile();
	std::string meta = base::FileSystem::GetFileMetaPath(uid);

	base::FileSystem::DeleteFile(file.c_str());
	base::FileSystem::DeleteFile(meta.c_str());

	if (resources_.find(uid) == resources_.end()) return;

	delete resources_[uid]; resources_[uid] = nullptr;
	resources_.erase(uid);
}

void bluefir::modules::ModuleResources::DeleteResource(const char * exported_file)
{
	std::string file = exported_file;
	
	size_t last_bracket = file.find_last_of('/');
	std::string uid = file.substr(last_bracket, file.find_last_of(".")-last_bracket);
	std::string meta = base::FileSystem::GetFileMetaPath(uid.c_str());
	
	base::FileSystem::DeleteFile(file.c_str());
	base::FileSystem::DeleteFile(meta.c_str());
}

bool bluefir::modules::ModuleResources::LoadMetaFile(const char * file)
{
	// Sanity Check
	if (!base::FileSystem::ExistsDir(file))	return false;
	if (std::strcmp(base::FileSystem::GetFileExtension(file), "meta") != 0) return false;

	// Import resource from json
	char* data = nullptr;
	base::FileSystem::ImportFile(file, &data);
	base::JSON* json = new base::JSON(data);
	resources::Resource* resource = resources::Importer::Import(json->GetString("file").c_str(), json->GetULongInt("uid"), json->GetInt("type"));
	if (resource == nullptr) return false;

	// Register resource
	resources_[json->GetULongInt("uid")] = resource;
	return true;
}
