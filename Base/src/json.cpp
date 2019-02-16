#include "json.h"

#include <string>

#include "BaseMacros.h"
#include "LogSystem.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

bluefir::base::JSON::JSON()
{
	document_ = new rapidjson::Document();
	document_->SetObject();
	allocator_ = &document_->GetAllocator();
}

bluefir::base::JSON::JSON(const char * buffer)
{
	document_ = new rapidjson::Document();
	document_->SetObject();
	document_->Parse(buffer);
	allocator_ = &document_->GetAllocator();
}

bluefir::base::JSON::~JSON()
{
	delete document_; document_ = nullptr;
}

void bluefir::base::JSON::FillBuffer(char ** buffer)
{
	if (*buffer != nullptr)
	{
		delete *buffer; *buffer = nullptr;
	}

	rapidjson::StringBuffer* json_buffer = new rapidjson::StringBuffer();
	rapidjson::Writer<rapidjson::StringBuffer> writer(*json_buffer);
	document_->Accept(writer);

	std::string s = json_buffer->GetString();
	*buffer = new char[s.size()];
	std::strcpy(*buffer, s.c_str());
}

void bluefir::base::JSON::SetBool(const char * name, bool value)
{
	ASSERT(name);

	rapidjson::Value json_key(name, std::strlen(name), *allocator_);
	rapidjson::Value::MemberIterator it = document_->FindMember(name);

	if (it != document_->MemberEnd()) it->value = rapidjson::Value(value);
	else document_->AddMember(json_key, rapidjson::Value(value), *allocator_);
}

bool bluefir::base::JSON::GetBool(const char * name) const
{
	ASSERT(name);

	rapidjson::Value::MemberIterator it = document_->FindMember(name);
	if (it != document_->MemberEnd()) return it->value.GetBool();

	LOGWARNING("Unable to find %s member.", name);
	return NULL;
}

void bluefir::base::JSON::SetInt(const char * name, int value)
{
	ASSERT(name);

	rapidjson::Value json_key(name, std::strlen(name), *allocator_);
	rapidjson::Value::MemberIterator it = document_->FindMember(name);

	if (it != document_->MemberEnd()) it->value = rapidjson::Value(value);
	else document_->AddMember(json_key, rapidjson::Value(value), *allocator_);
}

int bluefir::base::JSON::GetInt(const char * name) const
{
	ASSERT(name);

	rapidjson::Value::MemberIterator it = document_->FindMember(name);
	if (it != document_->MemberEnd()) return it->value.GetInt();
	
	LOGWARNING("Unable to find %s member.", name); 
	return NULL;
}

void bluefir::base::JSON::SetUInt(const char * name, unsigned int value)
{
	ASSERT(name);

	rapidjson::Value json_key(name, std::strlen(name), *allocator_);
	rapidjson::Value::MemberIterator it = document_->FindMember(name);

	if (it != document_->MemberEnd()) it->value = rapidjson::Value(value);
	else document_->AddMember(json_key, rapidjson::Value(value), *allocator_);
}

unsigned int bluefir::base::JSON::GetUInt(const char * name) const
{
	ASSERT(name);

	rapidjson::Value::MemberIterator it = document_->FindMember(name);
	if (it != document_->MemberEnd()) return it->value.GetUint();

	LOGWARNING("Unable to find %s member.", name);
	return NULL;
}

void bluefir::base::JSON::SetULongInt(const char * name, unsigned long long int value)
{
	ASSERT(name);

	rapidjson::Value json_key(name, std::strlen(name), *allocator_);
	rapidjson::Value::MemberIterator it = document_->FindMember(name);

	if (it != document_->MemberEnd()) it->value = rapidjson::Value((uint64_t)value);
	else document_->AddMember(json_key, rapidjson::Value((uint64_t)value), *allocator_);
}

unsigned int bluefir::base::JSON::GetULongInt(const char * name) const
{
	rapidjson::Value::MemberIterator it = document_->FindMember(name);
	if (it != document_->MemberEnd()) return it->value.GetUint64();

	LOGWARNING("Unable to find %s member.", name);
	return NULL;
}

void bluefir::base::JSON::SetString(const char * name, const char* value)
{
	ASSERT(name);

	rapidjson::Value json_key(name, std::strlen(name), *allocator_);
	rapidjson::Value::MemberIterator it = document_->FindMember(name);

	if (it != document_->MemberEnd()) it->value = rapidjson::Value(value, strlen(value));
	else document_->AddMember(json_key, rapidjson::Value(value, strlen(value)), *allocator_);
}

std::string bluefir::base::JSON::GetString(const char * name) const
{
	ASSERT(name);

	rapidjson::Value::MemberIterator it = document_->FindMember(name);
	if (it != document_->MemberEnd())
	{
		return std::string(it->value.GetString());
	}

	LOGWARNING("Unable to find %s member.", name);
	return std::string();
}
