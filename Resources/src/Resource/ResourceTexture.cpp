#include "ResourceTexture.h"

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
