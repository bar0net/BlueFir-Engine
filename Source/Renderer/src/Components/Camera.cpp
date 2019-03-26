#include "Camera.h"

#include "Geometry/Frustum.h"
#include "Math/MathConstants.h"
#include "Math/float4x4.h"
#include "Math/float3.h"


#include "../ModuleRenderer.h"

#include "Graphics.h"
#include "Buffer/FrameBuffer.h"
#include "Buffer/RenderBuffer.h"
#include "Buffer/TextureBuffer.h"

bluefir::core::Camera::Camera(const GameObject* gameObject) : Component(gameObject, ComponentType::CAMERA)
{
	frustum_ = new Frustum();
	frustum_->pos = math::float3::zero;
	frustum_->front = -math::float3::unitZ;
	frustum_->up = math::float3::unitY;

	frustum_->nearPlaneDistance = 0.5F;
	frustum_->farPlaneDistance = 1000.0F;

	frustum_->horizontalFov = math::pi * 60 / 180.0F;
	frustum_->verticalFov = 2.0F * atan(tan(frustum_->horizontalFov / 2.0F) * ((float)modules::ModuleRenderer::getInstance().GetWindowHeight() / (float)modules::ModuleRenderer::getInstance().GetWindowWidth()));

	frustum_->type = math::FrustumType::PerspectiveFrustum;

	modules::ModuleRenderer::getInstance().AddCamera(this);
	
	int width  = modules::ModuleRenderer::getInstance().GetWindowWidth();
	int height = modules::ModuleRenderer::getInstance().GetWindowHeight();

	fbo_ = new graphics::FrameBuffer();
	rbo_ = new graphics::RenderBuffer();
	texture_ = new graphics::TextureBuffer(width, height);
	rbo_->SetStorage(width, height, BF_DEPTH_COMPONENT);
	fbo_->SetRenderBuffer(rbo_->ID(), BF_DEPTH_ATTACHMENT);
	fbo_->SetTexture(texture_->ID(), 0, BF_COLOR_ATTACHMENT0);

	if (!main_camera) main_camera = this;
}

bluefir::core::Camera::~Camera()
{
	modules::ModuleRenderer::getInstance().RemoveCamera(this);
	
	if (main_camera == this) main_camera = nullptr;

	if (frustum_)
	{
		delete frustum_; frustum_ = nullptr;
	}

	if (fbo_)
	{
		delete fbo_; fbo_ = nullptr;
	}

	if (rbo_)
	{
		delete rbo_; rbo_ = nullptr;
	}

	if (texture_) 
	{
		delete texture_; texture_ = nullptr;
	}
}

void bluefir::core::Camera::SetNearPlaneDistance(float value)
{
	frustum_->nearPlaneDistance = value;
}

void bluefir::core::Camera::SetFarPlaneDistance(float value)
{
	frustum_->farPlaneDistance = value;
}

void bluefir::core::Camera::SetFOV(float value)
{
	frustum_->horizontalFov = math::pi * value / 180.0F;
	frustum_->verticalFov = 2.0F * atan(tan(frustum_->horizontalFov / 2.0F) * ((float)modules::ModuleRenderer::getInstance().GetWindowHeight() / (float)modules::ModuleRenderer::getInstance().GetWindowWidth()));
}

float bluefir::core::Camera::GetNearPlaneDistance() const
{
	return frustum_->nearPlaneDistance;
}

float bluefir::core::Camera::GetFarPlaneDistance() const
{
	return frustum_->farPlaneDistance;
}

float bluefir::core::Camera::GetFOV() const
{
	return frustum_->horizontalFov * 180.0F / math::pi;
}

void bluefir::core::Camera::FrustumMatrix(float * matrix) const
{
	float4x4 m = frustum_->ProjectionMatrix();
	memcpy(matrix, m.ptr(), 16 * sizeof(float));
}

void bluefir::core::Camera::FrustumMatrixT(float * matrix) const
{
	float4x4 m = frustum_->ProjectionMatrix().Transposed();
	memcpy(matrix, m.ptr(), 16 * sizeof(float));
}

void bluefir::core::Camera::Bind() const
{
	if (fbo_) fbo_->Bind();
	else graphics::FrameBuffer::ForceUnBind();
}

void bluefir::core::Camera::UnBind() const
{
	fbo_->UnBind();
}

void bluefir::core::Camera::ForceUnBind()
{
	graphics::FrameBuffer::ForceUnBind();
}

void bluefir::core::Camera::ToEditorConfiguration()
{
	//render_contents_ = false;
	if (main_camera == this) main_camera = nullptr;
}

int bluefir::core::Camera::RenderTextureID()
{
	if (texture_) return texture_->ID();
	else return BF_INVALID_TEXTURE_ID;
}
