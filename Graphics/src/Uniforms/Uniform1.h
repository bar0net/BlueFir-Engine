#ifndef BF_GRAPHICS_UNIFORM1
#define BF_GRAPHICS_UNIFORM1

#include "../Uniform.h"

namespace bluefir::graphics
{
	template <class T>
	class Uniform1 : public UniformedTyped<T>
	{
		static_assert(std::is_fundamental_v<T>);

	public:
		Uniform1(int location, int size, unsigned int count)
			: UniformedTyped(location, size, count) { }

		virtual void Set(const void* data) const override { LOGERROR("Unsupported uniform type."); }
	};

	template <>
	class Uniform1<int> : public UniformedTyped<int>
	{
	public:
		Uniform1<int>::Uniform1(int location, int size, unsigned int count)
			: UniformedTyped(location, size, count) { }

		virtual void Set(const void* data) const override
		{
			ASSERT(data); 			
			GLCall(glUniform1i(location_, ((int*)data)[0]));
		}
	};

	template <>
	class Uniform1<float> : public UniformedTyped<float>
	{
	public:
		Uniform1<float>::Uniform1(int location, int size, unsigned int count)
			: UniformedTyped(location, size, count) { }

		virtual void Set(const void* data) const override
		{
			ASSERT(data);
			GLCall(glUniform1f(location_, ((float*)data)[0]));
		}
	};
}
#endif // !BF_GRAPHICS_UNIFORM1
