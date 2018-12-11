#ifndef BLUEFIR_BASE_FILESYS_H
#define BLUEFIR_BASE_FILESYS_H

namespace bluefir::base
{
	class FileSystem
	{
	public:
		static const char* ReadFile(const char* filename);
		static void LoadFile(const char* filename, char* data, int& size);

	private:
		FileSystem() = delete;
	};
}

#endif //!BLUEFIR_BASE_FILESYS_H