#ifndef BF_GRAPHICS_UNIFORM4
#define BF_GRAPHICS_UNIFORM4

#include "../Uniform.h"

namespace bluefir::graphics
{
	template <class T>
	class Uniform4 : public UniformedTyped<T>
	{
		static_assert(std::is_fundamental_v<T>);

	public:
		Uniform4(int location, int size, unsigned int count)
			: UniformedTyped(location, size, count)(location, size, count) { }

		virtual void Set(const void* data) const override { LOGERROR("Unsupported uniform type."); }
	};

	template <>
	class Uniform4<int> : public UniformedTyped<int>
	{
	public:
		Uniform4<int>::Uniform4(int location, int size, unsigned int count)
			: UniformedTyped(location, size, count) { }

		virtual void Set(const void* data) const override
		{
			ASSERT(data);
			GLCall(glUniform4i(location_, ((int*)data)[0], ((int*)data)[1], ((int*)data)[2], ((int*)data)[3]));
		}
	};

	template <>
	class Uniform4<float> : public UniformedTyped<float>
	{
	public:
		Uniform4<float>::Uniform4(int location, int size, unsigned int count)
			: UniformedTyped(location, size, count) { }

		virtual void Set(const void* data) const override
		{
			ASSERT(data);
			GLCall(glUniform4f(location_, ((float*)data)[0], ((float*)data)[1], ((float*)data)[2], ((float*)data)[3]));
		}
	};
}
#endif // !BF_GRAPHICS_UNIFORM4