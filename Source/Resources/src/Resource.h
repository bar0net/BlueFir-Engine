#ifndef BF_CORE_RESOURCE
#define BF_CORE_RESOURCE

#include <string>

#include "BaseMacros.h"

#define Config char

namespace bluefir::resources
{
	enum class Type 
	{
		UNKNOWN = 0,
		TEXTURE,
		MESH
	};

	class Resource
	{
	public:
		Resource(const char* exported_file) : exported_file_(exported_file) { }
		Resource(UID uid, const char* file, const char* exported_file, Type type, bool keep_in_memory = false) : uid_(uid), type_(type), keep_in_memory_(keep_in_memory) 
		{ file_ = std::string(file); exported_file_ = std::string(exported_file); };
		
		virtual ~Resource() {};
		
		inline UID GetUID() const { return uid_; }
		inline Type GetType() const { return type_; }
		inline const char* GetFile() const { return file_.c_str(); }
		bool CheckFile(const char* file) const { return strcmp(file, file_.c_str()) == 0; }
		inline const char* GetExportedFile() const { return exported_file_.c_str(); }
		inline unsigned int Count() const { return loaded_; }
		inline bool IsLoadedToMemory() const { return keep_in_memory_ || loaded_ > 0U; }


		virtual void Save() const {};
		virtual void Load() { };
		virtual bool LoadInMemory() = 0;
		virtual bool UnloadFromMemory(bool force = false) = 0;

	protected:
		UID uid_ = 0;
		std::string file_ = "INVALID_PATH";
		std::string exported_file_;

		Type type_ = Type::UNKNOWN;
		bool keep_in_memory_ = false;
		unsigned int loaded_ = 0U;
	};
}

#endif // BF_CORE_RESOURCE

