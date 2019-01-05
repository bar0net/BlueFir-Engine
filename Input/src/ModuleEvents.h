#ifndef BF_MODULES_INPUT
#define BF_MODULES_INPUT

#include "Module.h"

#define KEY_COUNT 300
#define MOUSE_KEY_COUNT 3

#define bluefir_event_module bluefir::modules::ModuleEvents::getInstance()
// TODO: Change name to ModuleEvents

namespace bluefir::modules
{
	class ModuleEvents : public Module
	{
	public:
		virtual ~ModuleEvents();
		static ModuleEvents& getInstance() { static ModuleEvents instance_; return instance_; }

		// Flow
		virtual bool Init() override;
		virtual UpdateState PreUpdate() override;
		virtual bool CleanUp() override;

	private:
		ModuleEvents();

		void UpdateKeyboardState();
		void UpdateMouseState();
		UpdateState ParseEvents();
	};
}

#endif // !BF_MODULES_INPUT
