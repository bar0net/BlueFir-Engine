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
	public:
		static bluefir::graphics::Mesh* Load(const char* data, unsigned int size);

	private:
		ModelLoader() = delete;
	
	};
}

#endif