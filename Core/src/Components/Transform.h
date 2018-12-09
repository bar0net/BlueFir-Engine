#ifndef BF_CORE_COMPONENTS_TRANSFORM
#define BF_CORE_COMPONENTS_TRANSFORM

#include "../Component.h"
namespace math
{
	class Quat;
	class float3;
	class float4x4;
}

namespace bluefir::core
{
	class GameObject;
}


namespace bluefir::core
{
	class Transform : public Component
	{
	public:
		Transform(const GameObject* gameObject);
		virtual ~Transform();
		static int Type() { return (int)ComponentType::TRANSFORM; }

		virtual void PreUpdate() override;

		void SetPosition(float x, float y, float z);
		void SetRotation(float x, float y, float z);
		void SetScale(float x, float y, float z);

		const float* GetPosition() const;
		const float* GetRotation() const;
		const float* GetScale() const;
		
		// Returns the Transformation Matrix as a Row Major array of float[16]
		void ModelMatrix(float* matrix) const;

		// Returns the Transformation Matrix as a Column Major array of float[16]
		void ModelMatrixT(float* matrix) const;

		// Returns the Inverse of the Transformation Matrix as a Row Major array of float[16]
		void ModelMatrixI(float* matrix) const;

		// Returns the Inverse of the Transformation Matrix as a Column Major array of float[16]
		void ModelMatrixIT(float* matrix) const;

		// Converts geospacial info to world coordinates
		void ToWorldCoordinates();

		// Converts geospacial info to local coordinates
		void ToLocalCoordinates();
		
	protected:
		math::float4x4* model_matrix_ = nullptr;

	private:
		math::float3* position_ = nullptr;
		math::Quat* rotation_ = nullptr;
		math::float3* scale_ = nullptr;

	};
}

#endif // !BF_CORE_COMPONENTS_TRANSFORM

