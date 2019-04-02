#include "ResourceTexture.h"
#include "BaseMacros.h"

#include "json.h"
#include "FileSystem.h"
#include "LogSystem.h"

#include "Buffer/TextureBuffer.h"
#include "../Importer.h"

bluefir::resources::ResourceTexture::~ResourceTexture()
{
	gpu_id = 0;
	delete buffer_; buffer_ = nullptr;
}

bool bluefir::resources::ResourceTexture::LoadInMemory()
{
	if (loaded_ == 0)
	{
		if (!base::FileSystem::ExistsDir(exported_file_.c_str()))
		{
			LOGERROR("Could not find file in library."); // TODO: Try to import when fails
			return false;
		}

		char* data = nullptr;
		int size = base::FileSystem::ImportFile(exported_file_.c_str(), &data);
		graphics::Graphics::ImportTexture(&buffer_, data, size, "dds");
		gpu_id = buffer_->ID();
		base::FileSystem::ReleaseFile(&data);
	}

	++loaded_;
	return true;
}

bool bluefir::resources::ResourceTexture::UnloadFromMemory(bool force)
{
	--loaded_;

	if (loaded_ > 0) return true;
	loaded_ = 0;

	if (keep_in_memory_ && !force) return true;

	gpu_id = 0;
	delete buffer_; buffer_ = nullptr;

	return true;
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
	if (loaded_ != 0) return;
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

	if (keep_in_memory_) Load();
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
