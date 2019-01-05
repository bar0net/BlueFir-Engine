#ifndef BF_MODULE_RENDERER
#define BF_MODULE_RENDERER

#include "Module.h"

#include <list>
#include <vector>
#include <unordered_map>
#include <string>

#include "StandardModels.h"

#define bluefir_renderer bluefir::modules::ModuleRenderer::getInstance()

// TODO:
// Need game object with transform to complete the draw pipeline
// Need Material class that parses uniforms to complete the draw pipeline

namespace bluefir::graphics
{
	struct WindowData;
	class Mesh;
	class Shader;
	class BufferLayout;
}

namespace bluefir::core
{
	class Camera;
}

namespace bluefir::editor
{
	class PanelRenderer;
}

namespace bluefir::modules
{
	struct DrawCall
	{
		DrawCall(const float* model_matrix, bluefir::graphics::Mesh* mesh, bluefir::graphics::Shader* shader)
			: mesh_(mesh), shader_(shader) { memcpy(model_, model_matrix, 16 * sizeof(float)); }

		float model_[16];
		const bluefir::graphics::Mesh* mesh_ = nullptr;
		bluefir::graphics::Shader* shader_ = nullptr;
	};

	class ModuleRenderer : public Module
	{
	public:
		static ModuleRenderer& getInstance() { static ModuleRenderer instance_; return instance_; }

		// Flow Methods
		virtual bool Init() override;
		virtual UpdateState PreUpdate() override;
		UpdateState Render();
		UpdateState Swap();
		virtual bool CleanUp() override;

		// Specific Methods
		void Draw(const float* model_matrix, int mesh_id, int shader_id);
		int CreateShader(const char* vShader, const char* fShader);
		int CreateMesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const graphics::BufferLayout* layout);
		int CreateMesh(graphics::ModelList model);

		// Event
		void ResizeEvent(unsigned int ID);

		// Accesors
		inline const graphics::WindowData* GetWindowData() const { return window_data_; }
		inline int GetWindowWidth() const { return width_; }
		inline int GetWindowHeight() const { return height_; }
		inline float GetAspectRatio() const { return (float)width_ / (float)height_; }
		inline float* GetClearColor() const { return (float*)clear_color_; }
		inline void SetClearColor(float r, float g, float b, float a) { clear_color_[0] = r; clear_color_[1] = g; clear_color_[2] = b; clear_color_[3] = a;	UpdateClearColor(); }
		void UpdateClearColor();

		void AddCamera(const core::Camera* camera);
		void RemoveCamera(const core::Camera* camera);

		// Utils
		void RenderCamera(const core::Camera* cam);

	private:
		int width_ = 1280U;
		int height_ = 720U;
		bool vsync_ = true;
		float clear_color_[4] = { 0.3F, 0.3F, 0.3F, 1.0F };
		float depth_ = 1.0F;

		graphics::WindowData* window_data_ = nullptr;
		std::list<DrawCall> draw_calls_;

		std::vector<const core::Camera*> cameras_;

		int shader_counter_ = 0;
		std::unordered_map<int, graphics::Shader*> shader_ids_;
		std::unordered_map<std::string, int> shader_names_;

		int mesh_counter_ = 0;
		std::unordered_map<int, graphics::Mesh*> meshes_;

		friend class bluefir::editor::PanelRenderer;
	};
}
#endif // !BF_MODULE_RENDERER

