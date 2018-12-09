#include "Camera.h"

#include "../Vendor/MathGeoLib/Geometry/Frustum.h"
#include "../Vendor/MathGeoLib/Math/MathConstants.h"
#include "../Vendor/MathGeoLib/Math/float4x4.h"
#include "../Vendor/MathGeoLib/Math/float3.h"

#include "../ModuleRenderer.h"

bluefir::core::Camera::Camera(const GameObject* gameObject) : Component(gameObject, ComponentType::CAMERA)
{
	frustum_ = new Frustum();
	frustum_->pos = math::float3::zero;
	frustum_->front = -math::float3::unitZ;
	frustum_->up = math::float3::unitY;

	frustum_->nearPlaneDistance = 0.1F;
	frustum_->farPlaneDistance = 1000.0F;

	frustum_->horizontalFov = math::pi * 60 / 180.0F;
	frustum_->verticalFov = 2.0F * atan(tan(frustum_->horizontalFov / 2.0F) * ((float)modules::ModuleRenderer::getInstance().GetWindowHeight() / (float)modules::ModuleRenderer::getInstance().GetWindowWidth()));

	frustum_->type = math::FrustumType::PerspectiveFrustum;

	modules::ModuleRenderer::getInstance().AddCamera(this);
}

bluefir::core::Camera::~Camera()
{
	modules::ModuleRenderer::getInstance().RemoveCamera(this);
	delete frustum_; frustum_ = nullptr;
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
