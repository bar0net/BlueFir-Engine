#ifndef BF_RESOURCE_IMPORTER
#define BF_RESOURCE_IMPORTER

namespace bluefir::resources
{
	class Importer
	{
	public:
		// Loads the "file_in_assets" texture and fills the "data" buffer
		// with the texture in DDS format.
		static unsigned int Texture(const char* file_in_assets, char** data);
		static void TextureInfo(const char* data, int size, int* width, int* height, int* depth, int* mips, int* bytes, int* format);

	private:
		Importer() = delete;
	};
}


#endif // !BF_RESOURCE_IMPORTER

