#ifndef BF_GRAPHICS_UNIFORM3
#define BF_GRAPHICS_UNIFORM3

#include "../Uniform.h"

namespace bluefir::graphics
{
	template <class T>
	class Uniform3 : public UniformedTyped<T>
	{
		static_assert(std::is_fundamental_v<T>);

	public:
		Uniform3(int location, int size, unsigned int count)
			: UniformedTyped(location, size, count, UniformType::VEC3, UniformPrimitive::NONE) { }

		virtual void Set(const void* data) const override { LOGERROR("Unsupported uniform type."); }
	};

	template <>
	class Uniform3<int> : public UniformedTyped<int>
	{
	public:
		Uniform3<int>::Uniform3(int location, int size, unsigned int count)
			: UniformedTyped(location, size, count, UniformType::VEC3, UniformPrimitive::INT) { }

		virtual void Set(const void* data) const override
		{
			ASSERT(data);
			GLCall(glUniform3i(location_, ((int*)data)[0], ((int*)data)[1], ((int*)data)[2]));
		}
	};

	template <>
	class Uniform3<float> : public UniformedTyped<float>
	{
	public:
		Uniform3<float>::Uniform3(int location, int size, unsigned int count)
			: UniformedTyped(location, size, count, UniformType::VEC3, UniformPrimitive::FLOAT) { }

		virtual void Set(const void* data) const override
		{
			ASSERT(data);
			GLCall(glUniform3f(location_, ((float*)data)[0], ((float*)data)[1], ((float*)data)[2]));
		}
	};
}
#endif // !BF_GRAPHICS_UNIFORM3