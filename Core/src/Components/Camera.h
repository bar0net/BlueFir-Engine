#ifndef BF_CORE_COMPONENT_CAMERA
#define BF_CORE_COMPONENT_CAMERA

#include "../Component.h"

namespace bluefir::core
{
	class Camera : public Component
	{
	public:
		virtual ~Camera() {}

		static ComponentType Type() { return ComponentType::CAMERA; }
	};
}
#endif // !BF_CORE_COMPONENT_CAMERA

