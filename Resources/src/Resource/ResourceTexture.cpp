#include "ResourceTexture.h"
#include "BaseMacros.h"

#include "json.h"
#include "FileSystem.h"
#include "LogSystem.h"

bool bluefir::resources::ResourceTexture::LoadInMemory()
{
	++loaded_;

	// TODO: Load Texture

	return false;
}

bool bluefir::resources::ResourceTexture::UnloadFromMemory(bool force)
{
	--loaded_;

	if (loaded_ > 0) return true;
	loaded_ = 0;

	if (keep_in_memory_ && !force) return true;

	// TODO: Unload Texture

	return false;
}

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
	std::string path = base::FileSystem::GetFileMetaPath(uid_);
	base::FileSystem::ExportFile(path.c_str(), buffer, strlen(buffer));
}

void bluefir::resources::ResourceTexture::Load()
{
	ASSERT(!exported_file_.empty());
	char* data = nullptr;
	
	size_t last_bracket = exported_file_.find_last_of("\\");
	if (last_bracket == std::string::npos)
	{
		size_t last_bracket = exported_file_.find_last_of("/");

		if (last_bracket == std::string::npos)
		{
			LOGERROR("Could not extract filename from %s", exported_file_);
			return;
		}
		else last_bracket += 1;
	}
	else last_bracket += 1;
	std::string str_uid = exported_file_.substr(last_bracket, exported_file_.find_last_of(".") - last_bracket);
	std::string path = base::FileSystem::GetFileMetaPath(str_uid.c_str(), &path);

	if (!base::FileSystem::ExistsDir(path.c_str())) return;

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

void bluefir::resources::ResourceTexture::Set(unsigned int width, unsigned int height, unsigned int depth, unsigned int mips, unsigned int bytes, int format)
{
	this->width  = width;
	this->height = height;
	this->depth  = depth;
	this->mips   = mips;
	this->bytes  = bytes;
	this->format = (TextureFormat)format;
}
