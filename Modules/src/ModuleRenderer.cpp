#include "ModuleRenderer.h"

#include "Shader.h"
#include "Mesh.h"
#include "Graphics.h"

#include "GameObject.h"
#include "Components/Camera.h"
#include "Components/Transform.h"

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
		float proj[16];
		float view[16];
		float model[16];

		for (auto it = cameras_.begin(); it != cameras_.end(); ++it)
		{
			dc.shader->Bind();
			dc.mesh->Bind();
			(*it)->FrustumMatrixT(proj);
			(*it)->gameObject_->transform_->ModelMatrixT(view);

			dc.shader->SetUniform("proj", proj);
			dc.shader->SetUniform("view", proj);
			bluefir::graphics::Graphics::Draw(dc.mesh->indices_.size());
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
	graphics::Graphics::DestroyWindow(window_data_);

	delete window_data_; window_data_ = nullptr;

	return true;
}

void bluefir::modules::ModuleRenderer::Draw(const bluefir::graphics::Mesh & mesh, const bluefir::graphics::Shader& shader)
{
	DrawCall c;
	c.mesh = &mesh;
	c.shader = &shader;
	draw_calls_.push(c);
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
	LOGINFO("Registering camera to renderer.");

	for (auto it = cameras_.begin(); it != cameras_.end(); ++it)
	{
		if (*it == camera) 
		{
			LOGWARNING("Renderer already has the camera registered.");
			return;
		}
	}

	cameras_.push_back(camera);
}

void bluefir::modules::ModuleRenderer::RemoveCamera(const core::Camera * camera)
{
	LOGINFO("Removing camera from renderer.");
	for (auto it = cameras_.begin(); it != cameras_.end(); ++it)
	{
		if (*it == camera)
		{
			cameras_.erase(it);
			return;
		}
	}
	LOGWARNING("Renderer didn't have the camera registered.");
}


