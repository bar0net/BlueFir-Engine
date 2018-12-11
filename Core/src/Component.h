#ifndef BF_CORE_COMPONENT
#define BF_CORE_COMPONENT

namespace bluefir::editor
{
	class ComponentSection;
}

namespace bluefir::core
{
	class GameObject;

	enum class ComponentType
	{
		NONE = 0,
		TRANSFORM,
		CAMERA,
		MESH_RENDERER
	};

	class Component
	{
	public:
		Component(const GameObject* gameObject, ComponentType type = ComponentType::NONE);
		virtual ~Component();

		virtual void PreUpdate();
		virtual void Update();
		virtual void PostUpdate();

	public:
		const GameObject* gameObject_ = nullptr;
		const ComponentType type_ = ComponentType::NONE;

		friend editor::ComponentSection;
	};
}

#endif // !BF_CORE_COMPONENT