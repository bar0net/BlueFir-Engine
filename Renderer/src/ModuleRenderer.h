#ifndef BF_MODULE_RENDERER
#define BF_MODULE_RENDERER

#include "Module.h"

#include <queue>
#include <vector>
#include <unordered_map>
#include <string>

#include "StandardModels.h"

// TODO:
// Need game object with transform to complete the draw pipeline
// Need Material class that parses uniforms to complete the draw pipeline

namespace bluefir::graphics
{
	struct WindowData;
	struct Mesh;
	class Shader;
	class BufferLayout;
}

namespace bluefir::core
{
	class Camera;
}

namespace bluefir::modules
{
	struct DrawCall
	{
		float model[16];
		const bluefir::graphics::Mesh* mesh = nullptr;
		bluefir::graphics::Shader* shader = nullptr;
	};

	class ModuleRenderer : public Module
	{
	public:
		static ModuleRenderer& getInstance() { static ModuleRenderer instance_; return instance_; }

		// Flow Methods
		virtual bool Init() override;
		virtual UpdateState PreUpdate() override;
		UpdateState Render();
		virtual bool CleanUp() override;

		// Specific Methods
		void Draw(const float* model_matrix, int mesh_id, int shader_id);
		int CreateShader(const char* vShader, const char* fShader);
		int CreateMesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const graphics::BufferLayout& layout);
		int CreateMesh(graphics::ModelList model);

		// Event
		void ResizeEvent(unsigned int ID);

		// Accesors
		inline int GetWindowWidth() const { return width_; }
		inline int GetWindowHeight() const { return height_; }
		inline const graphics::WindowData* GetWindowData() const { return window_data_; }

		void AddCamera(const core::Camera* camera);
		void RemoveCamera(const core::Camera* camera);

	private:
		int width_ = 1280U;
		int height_ = 720U;
		bool vsync_ = true;
		float clear_color_[4] = { 0.3F, 0.3F, 0.3F, 1.0F };
		float depth_ = 1.0F;

		graphics::WindowData* window_data_ = nullptr;
		std::queue<DrawCall> draw_calls_;

		std::vector<const core::Camera*> cameras_;

		int shader_counter_ = 0;
		std::unordered_map<int, graphics::Shader*> shader_ids_;
		std::unordered_map<std::string, int> shader_names_;

		int mesh_counter_ = 0;
		std::unordered_map<int, graphics::Mesh*> meshes_;
	};
}
#endif // !BF_MODULE_RENDERER

