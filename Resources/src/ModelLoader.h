#ifndef BF_CORE_MODELLOADER
#define BF_CORE_MODELLOADER

#include <vector>

namespace bluefir::graphics
{
	class Mesh;
	class Material;
}

namespace bluefir::core
{
	class ModelLoader
	{
	public:
		static bool Load(const char* data, unsigned int size, std::vector<graphics::Mesh*>& meshes, std::vector <graphics::Material*> materials);

	private:
		ModelLoader() = delete;
	
	};
}

#endif