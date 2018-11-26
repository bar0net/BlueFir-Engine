#ifndef BF_GRAPHICS_UNIFORM4x4
#define BF_GRAPHICS_UNIFORM4x4

#include "../Uniform.h"

namespace bluefir::graphics
{
	template <class T>
	class Uniform4x4 : public UniformedTyped<T>
	{
		static_assert(std::is_fundamental_v<T>);

	public:
		Uniform4x4(int location, int size, unsigned int count)
			: UniformedTyped(location, size, count) { }

		virtual void Set(int location, const void* data) const override { LOGERROR("Unsupported uniform type."); }
	};

	template <>
	class Uniform4x4<float> : public UniformedTyped<float>
	{
	public:
		Uniform4x4<float>::Uniform4x4(int location, int size, unsigned int count)
			: UniformedTyped(location, size, count) { }

		virtual void Set(const void* data) const override
		{
			ASSERT(data);
			GLCall(glUniformMatrix4fv(location_, 1, true, (float*)data));
		}
	};
}
#endif // !BF_GRAPHICS_UNIFORM4x4