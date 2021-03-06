#ifndef BLUEFIR_BASE_JSON_H
#define BLUEFIR_BASE_JSON_H

#include <string>

namespace bluefir::base
{
	class JSON
	{
	public:
		JSON();
		JSON(const char* buffer);
		virtual ~JSON();

		void FillBuffer(char** buffer);

		void SetBool(const char* name, bool value);
		bool GetBool(const char* name) const;

		void SetInt(const char* name, int value);
		int GetInt(const char* name) const;

		void SetUInt(const char* name, unsigned int value);
		unsigned int GetUInt(const char* name) const;

		void SetULongInt(const char* name, unsigned long long int value);
		unsigned long long int GetULongInt(const char* name) const;

		void SetString(const char* name, const char* value);
		std::string GetString(const char* name) const;

	private:
		void* document_ptr_ = nullptr; //rapidjson::Document
		void* allocator_ = nullptr; //rapidjson::Document::AllocatorType

	};
}

#endif //!BLUEFIR_BASE_JSON_H