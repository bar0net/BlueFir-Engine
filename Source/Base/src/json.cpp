#include "json.h"

#include <string.h>
#include "rapidjson/document.h"

#include "BaseMacros.h"
#include "LogSystem.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

#define document_ ((rapidjson::Document*)document_ptr_)

bluefir::base::JSON::JSON()
{
	document_ptr_ = (void*)(new rapidjson::Document());
	document_->SetObject();
	allocator_ = &document_->GetAllocator();
}

bluefir::base::JSON::JSON(const char * buffer)
{
	document_ptr_ = new rapidjson::Document();
	document_->SetObject();
	document_->Parse(buffer);
	allocator_ = &document_->GetAllocator();
}

bluefir::base::JSON::~JSON()
{
	if (document_ != nullptr) { delete document_; document_ptr_ = nullptr; }
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
	strcpy_s(*buffer, s.size(), s.c_str());

	delete json_buffer;
}

void bluefir::base::JSON::SetBool(const char * name, bool value)
{
	ASSERT(name);

	rapidjson::Value json_key(name, (rapidjson::SizeType)std::strlen(name), *(rapidjson::Document::AllocatorType*)(allocator_));
	rapidjson::Value::MemberIterator it = document_->FindMember(name);

	if (it != document_->MemberEnd()) it->value = rapidjson::Value(value);
	else document_->AddMember(json_key, rapidjson::Value(value), *(rapidjson::Document::AllocatorType*)(allocator_));
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

	rapidjson::Value json_key(name, (rapidjson::SizeType)std::strlen(name), *(rapidjson::Document::AllocatorType*)(allocator_));
	rapidjson::Value::MemberIterator it = document_->FindMember(name);

	if (it != document_->MemberEnd()) it->value = rapidjson::Value(value);
	else document_->AddMember(json_key, rapidjson::Value(value), *(rapidjson::Document::AllocatorType*)(allocator_));
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

	rapidjson::Value json_key(name, (rapidjson::SizeType)std::strlen(name), *(rapidjson::Document::AllocatorType*)(allocator_));
	rapidjson::Value::MemberIterator it = document_->FindMember(name);

	if (it != document_->MemberEnd()) it->value = rapidjson::Value(value);
	else document_->AddMember(json_key, rapidjson::Value(value), *(rapidjson::Document::AllocatorType*)(allocator_));
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

	rapidjson::Value json_key(name, (rapidjson::SizeType)std::strlen(name), *(rapidjson::Document::AllocatorType*)(allocator_));
	rapidjson::Value::MemberIterator it = document_->FindMember(name);

	if (it != document_->MemberEnd()) it->value = rapidjson::Value((uint64_t)value);
	else document_->AddMember(json_key, rapidjson::Value((uint64_t)value), *(rapidjson::Document::AllocatorType*)(allocator_));
}

unsigned long long int bluefir::base::JSON::GetULongInt(const char * name) const
{
	rapidjson::Value::MemberIterator it = document_->FindMember(name);
	if (it != document_->MemberEnd()) return it->value.GetUint64();

	LOGWARNING("Unable to find %s member.", name);
	return NULL;
}

void bluefir::base::JSON::SetString(const char * name, const char* value)
{
	ASSERT(name);

	rapidjson::Value json_key(name, (rapidjson::SizeType)std::strlen(name), *(rapidjson::Document::AllocatorType*)(allocator_));
	rapidjson::Value::MemberIterator it = document_->FindMember(name);

	if (it != document_->MemberEnd()) it->value = rapidjson::Value(value, (rapidjson::SizeType)std::strlen(value));
	else document_->AddMember(json_key, rapidjson::Value(value, (rapidjson::SizeType)std::strlen(value)), *(rapidjson::Document::AllocatorType*)(allocator_));
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
