#include "ModuleRenderer.h"

#include "FileSystem.h"

#include "Shader.h"
#include "Mesh.h"
#include "Graphics.h"

#include "Components/Camera.h"
#include "Components/Transform.h"

#include "GameObject.h"

#define BF_REND_SEPARATOR "__"

bool bluefir::modules::ModuleRenderer::Init()
{
	LOGINFO("Initializing renderer.");
	window_data_ = graphics::Graphics::StartWindow("BlueFir Engine", width_, height_);

	if (!window_data_->valid)
	{
		LOGERROR("Failed to create a window.");
		return false;
	}

	LOGINFO("Window created successfully.");
	
	graphics::Graphics::CreateViewport(width_, height_, clear_color_, depth_);

	return true;
}

bluefir::modules::UpdateState bluefir::modules::ModuleRenderer::PreUpdate()
{
	graphics::Graphics::ClearViewport();

	return UpdateState::Update_Continue;
}

bluefir::modules::UpdateState bluefir::modules::ModuleRenderer::Render()
{
	for (auto it = cameras_.begin(); it != cameras_.end(); ++it)
		RenderCamera(*it);

	return UpdateState::Update_Continue;
}

bluefir::modules::UpdateState bluefir::modules::ModuleRenderer::Swap()
{
	// Swap windows
	graphics::Graphics::SwapWindow(window_data_);
	draw_calls_.clear();

	return UpdateState::Update_Continue;
}

bool bluefir::modules::ModuleRenderer::CleanUp()
{
	LOGINFO("Closing renderer.");
	// Delete Shaders
	for (auto it = shader_ids_.begin(); it != shader_ids_.end(); ++it)
		delete it->second;
	shader_ids_.clear();
	shader_names_.clear();

	// Delete Meshes
	for (auto it = meshes_.begin(); it != meshes_.end(); ++it)
		delete it->second;
	meshes_.clear();

	// Delete Viewport
	graphics::Graphics::DestroyWindow(window_data_);
	delete window_data_; window_data_ = nullptr;

	return true;
}

void bluefir::modules::ModuleRenderer::Draw(const float* model_matrix, int mesh, int shader_id)
{
	ASSERT(model_matrix);

	if (shader_id < 0) return;

	float model[16];
	memcpy(model, model_matrix, 16 * sizeof(float));

	//TODO: Change transference method for model matrix to reduce the number of copies!
	draw_calls_.emplace_back(model, meshes_[mesh], shader_ids_[shader_id]);
}

int bluefir::modules::ModuleRenderer::CreateShader(const char * vShader, const char * fShader)
{
	ASSERT(vShader && fShader);
	std::string name = std::string(vShader) + std::string(BF_REND_SEPARATOR) + std::string(fShader);

	auto it = shader_names_.find(name);
	if (it != shader_names_.end())
	{
		LOGINFO("Shader <%s> is already registered.", name);
		return it->second;
	}

	const char* vContent = base::FileSystem::ReadFile(vShader);
	const char* fContent = base::FileSystem::ReadFile(fShader);

	bluefir::graphics::Shader* shader = new bluefir::graphics::Shader(vContent, fContent);

	delete vContent; vContent = nullptr;
	delete fContent; fContent = nullptr;

	if (!shader->valid)
	{
		LOGERROR("Could not create the shader <%s>.", name);
		delete shader; shader = nullptr;
		return -1;
	}

	shader_names_[name] = shader_counter_;
	shader_ids_[shader_counter_] = shader;
	++shader_counter_;

	return (shader_counter_ - 1);
}

int bluefir::modules::ModuleRenderer::CreateMesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const graphics::BufferLayout & layout)
{
	meshes_[mesh_counter_] = new graphics::Mesh(vertices, indices, layout);
	meshes_[mesh_counter_]->Build();
	++mesh_counter_;

	return mesh_counter_ - 1;
}

int bluefir::modules::ModuleRenderer::CreateMesh(graphics::ModelList model)
{
	meshes_[mesh_counter_] = graphics::StandardModels::Get(model);
	++mesh_counter_;

	return mesh_counter_ - 1;
}

void bluefir::modules::ModuleRenderer::ResizeEvent(unsigned int ID)
{
	ASSERT(window_data_);
	LOGINFO("Resize event detected.");

	if (ID != graphics::Graphics::GetWindowID(window_data_)) return;

	graphics::Graphics::GetWindowSize(window_data_, width_, height_);
	graphics::Graphics::ChangeViewportSize(width_, height_);
}

void bluefir::modules::ModuleRenderer::UpdateClearColor()
{
	graphics::Graphics::ChangeClearColor(clear_color_);
}

void bluefir::modules::ModuleRenderer::AddCamera(const core::Camera * camera)
{
	ASSERT(camera);
	for (auto it = cameras_.begin(); it != cameras_.end(); ++it)
	{
		if (*it == camera)
		{
			LOGWARNING("Camera already registered.");
			return;
		}
	}

	cameras_.push_back(camera);
}

void bluefir::modules::ModuleRenderer::RemoveCamera(const core::Camera * camera)
{
	ASSERT(camera);
	for (auto it = cameras_.begin(); it != cameras_.end(); ++it)
	{
		if (*it == camera)
		{
			cameras_.erase(it);
			return;
		}
	}

	LOGWARNING("Trying to remove a camera that is not registered in the module.");
}

void bluefir::modules::ModuleRenderer::RenderCamera(const core::Camera * cam)
{
	// Remember: Proj and View must be sent as COLUMN Major!
	float proj[16]; cam->FrustumMatrixT(proj);
	float view[16]; cam->gameObject_->transform->ModelMatrixIT(view);

	// ASUMTION: All shaders include a UniformBlock (layout 140) with view and proj
	draw_calls_.front().shader_->SetUniform("view", view);
	draw_calls_.front().shader_->SetUniform("proj", proj);

	for (auto it = draw_calls_.begin(); it != draw_calls_.end(); ++it)
	{
		it->shader_->Bind();
		it->mesh_->Bind();
		it->shader_->SetUniform("model", it->model_);

		if (it->mesh_->type_ == graphics::MeshType::TRIANGLE)
			bluefir::graphics::Graphics::Draw((unsigned int)it->mesh_->indices_.size());

		else if (it->mesh_->type_ == graphics::MeshType::LINE)
			bluefir::graphics::Graphics::DrawLines((unsigned int)it->mesh_->indices_.size());
	}

	/*
	while (!draw_calls_.empty())
	{
		DrawCall dc = draw_calls_.front();
		dc.shader_->Bind();
		for (auto it = cameras_.begin(); it != cameras_.end(); ++it)
		{
			dc.shader_->SetUniform("view", view);
			dc.shader_->SetUniform("proj", proj);
		}
		draw_calls_.pop();
	}*/
}


