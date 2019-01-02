#ifndef BF_CORE_COMPONENT_CAMERA
#define BF_CORE_COMPONENT_CAMERA

#include "Component.h"

#define BF_INVALID_TEXTURE_ID -1

namespace math
{
	class Frustum;
}

namespace bluefir::core
{
	class GameObject;
}

namespace bluefir::graphics
{
	class FrameBuffer;
	class TextureBuffer;
	class RenderBuffer;
}

namespace bluefir::core
{
	class Camera : public Component
	{
	public:
		Camera(const GameObject* gameObject);
		virtual ~Camera();
		static int Type() { return (int)ComponentType::CAMERA; }

		void SetNearPlaneDistance(float value);
		void SetFarPlaneDistance(float value);
		void SetFOV(float value);

		float GetNearPlaneDistance() const;
		float GetFarPlaneDistance() const;
		float GetFOV() const;

		// Frustum Matrix (Row Major) as an array of float[16]
		void FrustumMatrix(float* matrix) const;

		//Frustum Matrix (Column Major) as an array of float[16]
		void FrustumMatrixT(float* matrix) const;

		void Bind() const;
		void UnBind() const;
		static void ForceUnBind();
		
		void ToEditorConfiguration();
		int RenderTextureID();

	public:
		bool render_contents_ = true;

	private:
		math::Frustum* frustum_ = nullptr;

		graphics::FrameBuffer* fbo_ = nullptr;
		graphics::RenderBuffer* rbo_ = nullptr;
		graphics::TextureBuffer* texture_ = nullptr;

		friend editor::ComponentSection;
	};
	static Camera* main_camera = nullptr;
}
#endif // !BF_CORE_COMPONENT_CAMERA

