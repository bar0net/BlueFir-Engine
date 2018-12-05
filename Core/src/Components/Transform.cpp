#include "Transform.h"

#include "../../Vendor/MathGeoLib/Math/float3.h"
#include "../../Vendor/MathGeoLib/Math/Quat.h"
#include "../../Vendor/MathGeoLib/Math/float4x4.h"
#include "../../Vendor/MathGeoLib/Math/MathConstants.h"

#define RAD2DEG 57.2957795F

bluefir::core::Transform::Transform()
{
	position_ = new float3(0.0F, 0.0F, 0.0F);
	rotation_ = new math::Quat(0,0,0,0);
	scale_ = new math::float3(1.0F, 1.0F, 1.0F);
}

bluefir::core::Transform::~Transform()
{
	delete position_;	position_ = nullptr;
	delete rotation_;	rotation_ = nullptr;
	delete scale_;		scale_ = nullptr;
}

void bluefir::core::Transform::SetPosition(float x, float y, float z)
{
	position_->Set(x, y, z);
}

void bluefir::core::Transform::SetRotation(float x, float y, float z)
{
	rotation_ = &Quat::FromEulerZXY(z, y, x);
}

void bluefir::core::Transform::SetScale(float x, float y, float z)
{
	scale_->Set(x / RAD2DEG, y / RAD2DEG, z / RAD2DEG);
}

const float * bluefir::core::Transform::GetPosition() const
{
	return position_->ptr();
}

const float * bluefir::core::Transform::GetRotation() const
{
	return (rotation_->ToEulerXYZ() * RAD2DEG).ptr();
}

const float * bluefir::core::Transform::GetScale() const
{
	return scale_->ptr();
}

void bluefir::core::Transform::ModelMatrix(float* matrix) const
{
	float4x4 m = math::float4x4::FromTRS(*position_, *rotation_, *scale_);
	memcpy(matrix, m.ptr(), 16 * sizeof(float));
}

void bluefir::core::Transform::ModelMatrixT(float * matrix) const
{
	float4x4 m = math::float4x4::FromTRS(*position_, *rotation_, *scale_).Transposed();
	memcpy(matrix, m.ptr(), 16 * sizeof(float));
}
