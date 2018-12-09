#ifndef BF_EDITOR_COMPONENTSECTION
#define BF_EDITOR_COMPONENTSECTION

namespace bluefir::core
{
	class Component;
	class Transform;
	class MeshRenderer;
	class Camera;
}


namespace bluefir::editor
{
	class ComponentSection
	{
	public:
		static void Display(core::Component* c);

	private:
		ComponentSection() = delete;

		static void DisplayTransform(core::Transform* c);
		static void DisplayMeshRenderer(core::MeshRenderer* c);
		static void DisplayCamera(core::Camera* c);
	};
}

#endif // !BF_EDITOR_COMPONENTSECTION

