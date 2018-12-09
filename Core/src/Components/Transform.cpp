#include "Transform.h"

#include "BaseMacros.h"
#include "../../Vendor/MathGeoLib/Math/float3.h"
#include "../../Vendor/MathGeoLib/Math/Quat.h"
#include "../../Vendor/MathGeoLib/Math/float4x4.h"
#include "../../Vendor/MathGeoLib/Math/MathConstants.h"

#include "../GameObject.h"

#define RAD2DEG 57.2957795F

bluefir::core::Transform::Transform(const GameObject* gameObject) : Component(gameObject)
{
	ASSERT(gameObject);

	position_ = new float3(0.0F, 0.0F, 0.0F);
	rotation_ = new math::Quat(0,0,0,0);
	scale_ = new math::float3(1.0F, 1.0F, 1.0F);

	this->model_matrix_ = new float4x4(float4x4::identity);
}

bluefir::core::Transform::~Transform()
{
	delete position_;		position_ = nullptr;
	delete rotation_;		rotation_ = nullptr;
	delete scale_;			scale_ = nullptr;
	delete this->model_matrix_;	this->model_matrix_ = nullptr;
}

void bluefir::core::Transform::PreUpdate()
{
	if (gameObject_->GetParent() == nullptr) model_matrix_->Set(math::float4x4::FromTRS(*position_, *rotation_, *scale_));
	else model_matrix_->Set(*(gameObject_->GetParent()->transform->model_matrix_) * math::float4x4::FromTRS(*position_, *rotation_, *scale_));
}

void bluefir::core::Transform::SetPosition(float x, float y, float z)
{
	position_->Set(x, y, z);
}

void bluefir::core::Transform::SetRotation(float x, float y, float z)
{
	Quat q = Quat::FromEulerZXY(z / RAD2DEG, y / RAD2DEG, x / RAD2DEG);
	rotation_->Set(q.x, q.y, q.z, q.w);
}

void bluefir::core::Transform::SetScale(float x, float y, float z)
{
	scale_->Set(x, y, z);
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
	ASSERT(matrix);
	memcpy(matrix, model_matrix_->ptr(), 16 * sizeof(float));
}

void bluefir::core::Transform::ModelMatrixT(float * matrix) const
{
	ASSERT(matrix);
	memcpy(matrix, model_matrix_->Transposed().ptr(), 16 * sizeof(float));
}

void bluefir::core::Transform::ModelMatrixI(float* matrix) const
{
	ASSERT(matrix);
	memcpy(matrix, model_matrix_->Inverted().ptr(), 16 * sizeof(float));
}

void bluefir::core::Transform::ModelMatrixIT(float * matrix) const
{
	ASSERT(matrix);
	memcpy(matrix, model_matrix_->Inverted().Transposed().ptr(), 16 * sizeof(float));
}

void bluefir::core::Transform::ToWorldCoordinates()
{
	math::float3 scale = model_matrix_->GetScale();

	position_->Set(model_matrix_->TranslatePart().x, model_matrix_->TranslatePart().y, model_matrix_->TranslatePart().z);
	rotation_->Set(model_matrix_->RotatePart());
	scale_->Set(scale.x, scale.y, scale.z);
}

void bluefir::core::Transform::ToLocalCoordinates()
{
	float4x4 m;
	if (!gameObject_->GetParent()) m = *model_matrix_;
	else m = (*gameObject_->GetParent()->transform->model_matrix_) * *model_matrix_;
	math::float3 scale = m.GetScale();

	position_->Set(m.TranslatePart().x, m.TranslatePart().y, m.TranslatePart().z);
	rotation_->Set(m.RotatePart());
	scale_->Set(scale.x, scale.y, scale.z);
}
