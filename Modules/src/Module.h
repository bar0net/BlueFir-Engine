#ifndef BF_MODULE_H
#define BF_MODULE_H

#include "LogSystem.h"
#include "BaseMacros.h"

namespace bluefir::modules
{
	enum class UpdateState
	{
		Update_Continue = 1,
		Update_Error = 2,
		Update_End = 3
	};

	class Module
	{
	public:
		virtual ~Module() {}

		virtual bool Init() { return true; }
		virtual bool Start() { return true; }
		virtual UpdateState PreUpdate() { return UpdateState::Update_Continue; }
		virtual UpdateState Update() { return UpdateState::Update_Continue; }
		virtual UpdateState PostUpdate() { return UpdateState::Update_Continue; }
		virtual bool End() { return true; }
		virtual bool CleanUp() { return true; }
	};
}
#endif // !BF_MODULE_H

