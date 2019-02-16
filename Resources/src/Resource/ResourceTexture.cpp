#include "ResourceTexture.h"
#include "BaseMacros.h"

#include "json.h"
#include "FileSystem.h"

void bluefir::resources::ResourceTexture::Save() const
{
	base::JSON json;

	json.SetULongInt("uid", uid_);
	json.SetString("file", file_.c_str());
	json.SetString("exported_file", exported_file_.c_str());
	json.SetInt("type", (int)type_);
	json.SetBool("keep_in_memory", keep_in_memory_);

	json.SetInt("width", width);
	json.SetInt("height", height);
	json.SetInt("depth", depth);
	json.SetInt("mips", mips);
	json.SetInt("bytes", bytes);
	json.SetInt("format", (int)format);
	
	char* buffer = nullptr;
	json.FillBuffer(&buffer);
	std::string path = exported_file_.substr(0, exported_file_.find_last_of('.')) + ".meta";
	base::FileSystem::ExportFile(path.c_str(), buffer, strlen(buffer));
}

void bluefir::resources::ResourceTexture::Load()
{
	ASSERT(!exported_file_.empty());
	char* data = nullptr;
	std::string path = exported_file_.substr(0, exported_file_.find_last_of('.')) + ".meta";

	base::FileSystem::ImportFile(path.c_str(), &data);
	base::JSON json(data);
	base::FileSystem::ReleaseFile(&data);

	uid_ = json.GetULongInt("uid");
	file_ = json.GetString("file");
	type_ = (resources::Type)json.GetInt("type");
	keep_in_memory_ = json.GetBool("keep_in_memory");

	width = json.GetInt("width");
	height = json.GetInt("height");
	depth = json.GetInt("depth");
	mips = json.GetInt("mips");
	bytes = json.GetInt("bytes");
	format = (resources::TextureFormat)json.GetInt("format");


}
