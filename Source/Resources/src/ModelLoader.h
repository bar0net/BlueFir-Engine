#ifndef BF_CORE_MODELLOADER
#define BF_CORE_MODELLOADER

#include <vector>

struct aiNode;
struct aiScene;
struct aiMesh;
class Matrix4x4;

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
		static bool Load(const char* data, unsigned int size, std::vector<int>& meshes, std::vector<int>& materials);

	private:
		ModelLoader() = delete;

		static void ParseNode(const aiNode* const node, Matrix4x4* transform, const aiScene* const scene, std::vector<int>& meshes);
		static graphics::Mesh* CreateMesh(const aiMesh* const mesh, const Matrix4x4* transform);
	};
}

#endif