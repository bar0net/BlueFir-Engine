#ifndef BF_CORE_COMPONENT
#define BF_CORE_COMPONENT

namespace bluefir::core
{
	class GameObject;

	enum class ComponentType
	{
		NONE = 0,
		TRANSFORM,
		CAMERA
	};

	class Component
	{
	public:
		Component(const GameObject* gameObject) : gameObject_(gameObject) {};
		virtual ~Component() {}

	public:
		const GameObject* gameObject_ = nullptr;
	};
}

#endif // !BF_CORE_COMPONENT