#ifndef BF_GRAPHICS_UNIFORM
#define BF_GRAPHICS_UNIFORM

#include <vector>

#include "../../Vendor/glew-2.1.0/include/GL/glew.h"

#include "LogSystem.h"
#include "Graphics.h"


namespace bluefir::graphics
{
	class Uniform
	{
	public:
		Uniform(int location, int size, unsigned int count)
			: location_(location), size_(size), count_(count) { }
		virtual ~Uniform() = default;	

		virtual void Set(const void* data) const = 0;

	public:
		bool block_ = false;
		int location_ = 0;
		int size_ = 0;
		unsigned int count_ = 0;
	};

	template <class T>
	class UniformedTyped : public Uniform
	{
	public:
		UniformedTyped(int location, int size, unsigned int count)
			: Uniform(location, size, count) { }

		static_assert(std::is_fundamental_v<T>);
		virtual void Set(const void* data) const = 0;
	};
}
#endif // !BF_GRAPHICS_UNIFORM

