#ifndef BLUEFIR_BASE_FILESYS_H
#define BLUEFIR_BASE_FILESYS_H

namespace bluefir::base
{
	class FileSystem
	{
	public:
		static const char* ReadFile(const char* filename);
	};
}

#endif //!BLUEFIR_BASE_FILESYS_H