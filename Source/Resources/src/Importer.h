#ifndef BF_RESOURCE_IMPORTER
#define BF_RESOURCE_IMPORTER

#include <string>

#include "BaseMacros.h"

namespace bluefir::resources
{
	class Resource;

	class Importer
	{
	public:
		static Resource* Import(const char* file_in_assets, UID uid, unsigned int type);
		static Resource* Texture(const char* file_in_assets, UID uid);

	private:
		Importer() = delete;

		static std::string GetSaveFolder(UID uid);
	};
}


#endif // !BF_RESOURCE_IMPORTER

