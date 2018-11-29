#ifndef BF_MODULE_RENDERER
#define BF_MODULE_RENDERER

#include "Module.h"

#include "Graphics.h"

struct bluefir::graphics::WindowData;

namespace bluefir::modules
{
	class ModuleRenderer : public Module
	{
	public:
		virtual bool Init() override;
		virtual UpdateState PreUpdate() override;
		bool Render();
		virtual bool CleanUp() override;

	private:
		unsigned int width_ = 1280U;
		unsigned int height_ = 720U;
		bool vsync_ = true;
		float clear_color_[4] = { 0.3F, 0.3F, 0.3F, 1.0F };
		float depth_ = 1.0F;

		graphics::WindowData* window_data_ = nullptr;
	};


}
#endif // !BF_MODULE_RENDERER

