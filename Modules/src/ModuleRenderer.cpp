#include "ModuleRenderer.h"

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
	graphics::Graphics::SwapWindow(window_data_);

	return true;
}

bool bluefir::modules::ModuleRenderer::CleanUp()
{
	graphics::Graphics::DestroyWindow(window_data_);

	delete window_data_; window_data_ = nullptr;

	return true;
}


