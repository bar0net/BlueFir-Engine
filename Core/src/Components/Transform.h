#ifndef BF_CORE_COMPONENTS_TRANSFORM
#define BF_CORE_COMPONENTS_TRANSFORM

#include "../Component.h"
namespace math
{
	class Quat;
	class float3;
}

namespace bluefir::core
{
	class Transform : public Component
	{
	public:
		Transform();
		virtual ~Transform();
		static ComponentType Type() { return ComponentType::TRANSFORM; }

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

	private:
		math::float3* position_ = nullptr;
		math::Quat* rotation_ = nullptr;
		math::float3* scale_ = nullptr;
	};
}

#endif // !BF_CORE_COMPONENTS_TRANSFORM

