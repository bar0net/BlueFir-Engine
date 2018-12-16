#ifndef BLUEFIR_BASE_FILESYS_H
#define BLUEFIR_BASE_FILESYS_H

namespace bluefir::base
{
	class FileSystem
	{
	public:
		static const char* ReadFile(const char* filename);
		static int ImportFile(const char* filename, char* data);
		static void ReleaseFile(const char* data);

	private:
		FileSystem() = delete;
	};
}

#endif //!BLUEFIR_BASE_FILESYS_H