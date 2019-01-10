#ifndef BF_CORE_MODELLOADER
#define BF_CORE_MODELLOADER


namespace bluefir::graphics
{
	class Mesh;
}

namespace bluefir::core
{
	class ModelLoader
	{
		static bluefir::graphics::Mesh* Load(const char* path, unsigned int size);

	private:
		ModelLoader() = delete;
	
	};
}

#endif