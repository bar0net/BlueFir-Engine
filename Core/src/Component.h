#ifndef BF_CORE_COMPONENT
#define BF_CORE_COMPONENT

namespace bluefir::core
{
	enum class ComponentType
	{
		NONE = 0,
		TRANSFORM,
		CAMERA
	};

	class Component
	{
	public:
		virtual ~Component() {}
	};
}

#endif // !BF_CORE_COMPONENT