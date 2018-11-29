#ifndef BF_MODULE_RENDERER
#define BF_MODULE_RENDERER

#include "Module.h"

#include "Graphics.h"
#include <queue>

// TODO:
// Need game object with transform to complete the draw pipeline
// Need Material class that parses uniforms to complete the draw pipeline

namespace bluefir::graphics
{
	struct WindowData;
	struct Mesh;
}

namespace bluefir::modules
{
	struct DrawCall
	{
		const bluefir::graphics::Mesh* mesh = nullptr;
	};

	class ModuleRenderer : public Module
	{
	public:
		// Flow Methods
		virtual bool Init() override;
		virtual UpdateState PreUpdate() override;
		bool Render();
		virtual bool CleanUp() override;

		// Specific Methods
		void Draw(const bluefir::graphics::Mesh& mesh);

	private:
		unsigned int width_ = 1280U;
		unsigned int height_ = 720U;
		bool vsync_ = true;
		float clear_color_[4] = { 0.3F, 0.3F, 0.3F, 1.0F };
		float depth_ = 1.0F;

		graphics::WindowData* window_data_ = nullptr;
		std::queue<DrawCall> draw_calls_;
	};


}
#endif // !BF_MODULE_RENDERER
