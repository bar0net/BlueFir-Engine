#ifndef BF_CORE_COMPONENTS_MESHRENDERER
#define BF_CORE_COMPONENTS_MESHRENDERER

#include "Component.h"

namespace bluefir::graphics
{
	class Mesh;
	class Shader;
}

namespace bluefir::core
{
	class MeshRenderer : public Component
	{
	public:
		MeshRenderer(const GameObject* gameObject);
		virtual ~MeshRenderer();
		static int Type() { return (int)ComponentType::MESH_RENDERER; }

		virtual void Update() override;
		
		void SetMesh(int mesh) { mesh_ID_ = mesh; }
		void SetMaterial(int shader) { shader_ID_ = shader;  }

	private:
		int mesh_ID_ = -1;
		int shader_ID_ = -1;
	};
}
#endif // !BF_CORE_COMPONENTS_MESHRENDERER

