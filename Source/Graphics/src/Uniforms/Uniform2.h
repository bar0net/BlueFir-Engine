#ifndef BF_GRAPHICS_UNIFORM2
#define BF_GRAPHICS_UNIFORM2

#include "../Uniform.h"

namespace bluefir::graphics
{
	template <class T>
	class Uniform2 : public UniformedTyped<T>
	{
		static_assert(std::is_fundamental_v<T>);

	public:
		Uniform2(int location, int size, unsigned int count)
			: UniformedTyped(location, size, count, UniformType::VEC2, UniformPrimitive::NONE) { }

		virtual void Set(const void* data) const override { LOGERROR("Unsupported uniform type."); }
	};

	template <>
	class Uniform2<int> : public UniformedTyped<int>
	{
	public:
		Uniform2<int>::Uniform2(int location, int size, unsigned int count)
			: UniformedTyped(location, size, count, UniformType::VEC2, UniformPrimitive::INT) { }

		virtual void Set(const void* data) const override
		{
			ASSERT(data);
			GLCall(glUniform2i(location_, ((int*)data)[0], ((int*)data)[1]));
		}
	};

	template <>
	class Uniform2<float> : public UniformedTyped<float>
	{
	public:
		Uniform2<float>::Uniform2(int location, int size, unsigned int count)
			: UniformedTyped(location, size, count, UniformType::VEC2, UniformPrimitive::FLOAT) { }

		virtual void Set(const void* data) const override
		{
			ASSERT(data);
			GLCall(glUniform2f(location_, ((float*)data)[0], ((float*)data)[1]));
		}
	};
}
#endif // !BF_GRAPHICS_UNIFORM2