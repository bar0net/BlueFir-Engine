#ifndef BF_GRAPHICS_UNIFORM
#define BF_GRAPHICS_UNIFORM

#include <vector>

#include "../../Vendor/glew-2.1.0/include/GL/glew.h"

#include "LogSystem.h"
#include "Graphics.h"


namespace bluefir::graphics
{
	enum class UniformType
	{
		NONE = 0,
		SINGLE,
		VEC2,
		VEC3,
		VEC4,
		MAT4
	};

	enum class UniformPrimitive
	{
		NONE = 0,
		INT,
		FLOAT,
		TEXTURE
	};


	class Uniform
	{
	public:
		Uniform(int location, int size, unsigned int count, UniformType type, UniformPrimitive primitive)
			: location_(location), size_(size), count_(count), type_(type), primitive_(primitive) { }
		virtual ~Uniform() = default;	

		virtual void Set(const void* data) const = 0;

	public:
		bool block_ = false;
		int location_ = 0;
		int size_ = 0;
		unsigned int count_ = 0;
		UniformType type_ = UniformType::NONE;
		UniformPrimitive primitive_ = UniformPrimitive::NONE;
	};

	template <class T>
	class UniformedTyped : public Uniform
	{
	public:
		UniformedTyped(int location, int size, unsigned int count, UniformType type, UniformPrimitive primitive)
			: Uniform(location, size, count, type, primitive) { }

		static_assert(std::is_fundamental_v<T>);
		virtual void Set(const void* data) const = 0;
	};
}
#endif // !BF_GRAPHICS_UNIFORM

