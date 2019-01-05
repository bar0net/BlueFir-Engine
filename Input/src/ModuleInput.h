#ifndef BF_MODULES_INPUT
#define BF_MODULES_INPUT

#include "Module.h"

#define KEY_COUNT 300
#define MOUSE_KEY_COUNT 3

namespace bluefir::modules
{
	class ModuleInput : public Module
	{
	public:
		virtual ~ModuleInput();
		static ModuleInput& getInstance() { static ModuleInput instance_; return instance_; }

		// Flow
		virtual bool Init() override;
		virtual UpdateState PreUpdate() override;
		virtual bool CleanUp() override;

	private:
		ModuleInput();

		void UpdateKeyboardState();
		void UpdateMouseState();
		UpdateState ParseEvents();
	};
}

#endif // !BF_MODULES_INPUT
