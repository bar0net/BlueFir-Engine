#ifndef BF_CORE_COMPONENTS_TRANSFORM
#define BF_CORE_COMPONENTS_TRANSFORM

#include "../Component.h"

namespace bluefir::core
{
	class Transform : public Component
	{
	public:
		virtual ~Transform() {}

		static ComponentType Type() { return ComponentType::TRANSFORM; }
	};
}

#endif // !BF_CORE_COMPONENTS_TRANSFORM

