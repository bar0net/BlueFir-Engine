#ifndef BF_CORE_COMPONENT_CAMERA
#define BF_CORE_COMPONENT_CAMERA

#include "../Component.h"

namespace math
{
	class Frustum;
}

namespace bluefir::core
{
	class Camera : public Component
	{
	public:
		Camera();
		virtual ~Camera();
		static ComponentType Type() { return ComponentType::CAMERA; }

		void SetNearPlaneDistance(float value);
		void SetFarPlaneDistance(float value);
		void SetFOV(float value, float height, float width);

		float GetNearPlaneDistance() const;
		float GetFarPlaneDistance() const;
		float GetFOV() const;

		// Frustum Matrix (Row Major) as an array of float[16]
		void FrustumMatrix(float* matrix);

		//Frustum Matrix (Column Major) as an array of float[16]
		void FrustumMatrixT(float* matrix);

	private:
		math::Frustum* frustum_ = nullptr;
	};
}
#endif // !BF_CORE_COMPONENT_CAMERA

