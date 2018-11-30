#include "ModuleRenderer.h"

#include "Shader.h"
#include "Mesh.h"
#include "Graphics.h"

bool bluefir::modules::ModuleRenderer::Init()
{
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

bool bluefir::modules::ModuleRenderer::Render()
{
	//TODO: Render all draw calls
	while (!draw_calls_.empty())
	{
		DrawCall dc = draw_calls_.front();
		dc.shader->Bind();
		dc.mesh->Bind();
		bluefir::graphics::Graphics::Draw(dc.mesh->indices_.size());

		draw_calls_.pop();
	}

	// Swap windows
	graphics::Graphics::SwapWindow(window_data_);

	return true;
}

bool bluefir::modules::ModuleRenderer::CleanUp()
{
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


