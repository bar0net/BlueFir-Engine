#include "ModuleRenderer.h"

#include "FileSystem.h"

#include "Shader.h"
#include "Mesh.h"
#include "Graphics.h"

#include "Components/Camera.h"
#include "Components/Transform.h"

#include "GameObject.h"

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
	while (!draw_calls_.empty())
	{
		DrawCall dc = draw_calls_.front();
		dc.shader->Bind();
		dc.mesh->Bind();
		dc.shader->SetUniform("model", dc.model);
		for (auto it = cameras_.begin(); it != cameras_.end(); ++it)
		{
			// Remember: Proj and View must be sent as COLUMN Major!
			float proj[16]; (*it)->FrustumMatrixT(proj);
			float view[16]; (*it)->gameObject_->transform->ModelMatrixIT(view);
			dc.shader->SetUniform("view", view);
			dc.shader->SetUniform("proj", proj);
			bluefir::graphics::Graphics::Draw((unsigned int)dc.mesh->indices_.size());
		}
		draw_calls_.pop();
	}

	// Swap windows
	graphics::Graphics::SwapWindow(window_data_);

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

	DrawCall c;
	//TODO: Change transference method for model matrix to reduce the number of copies!
	memcpy(c.model, model_matrix, 16 * sizeof(float));
	c.mesh = meshes_[mesh];
	c.shader = shader_ids_[shader_id];
	draw_calls_.push(c);
}

int bluefir::modules::ModuleRenderer::CreateShader(const char * vShader, const char * fShader)
{
	ASSERT(vShader && fShader);
	std::string name = std::string(vShader) + std::string("##") + std::string(fShader);

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

	return 0;
}

void bluefir::modules::ModuleRenderer::ResizeEvent(unsigned int ID)
{
	ASSERT(window_data_);
	LOGINFO("Resize event detected.");

	if (ID != graphics::Graphics::GetWindowID(window_data_)) return;

	graphics::Graphics::GetWindowSize(window_data_, width_, height_);
	graphics::Graphics::ChangeViewportSize(width_, height_);
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


