#ifndef BF_GRAPHICS_MATERIAL
#define BF_GRAPHICS_MATERIAL

#include <unordered_map>
#include <string>

#include "Uniform.h"
// TODO: We only need an enum class from Uniforms.h
// maybe we should separate the enums into a seperate .h

namespace bluefir::graphics
{
	class Shader;

	struct MaterialAttrib 
	{ 
		UniformPrimitive type_ = UniformPrimitive::NONE;
		unsigned int size_ = 0;
	};

	template <class T, unsigned int M>
	struct MaterialAttribData : public MaterialAttrib
	{
		// TODO: CORRECT THIS!!!!
		template<class T>
		MaterialAttribData() : type_(UniformPrimitive::NONE), size_(M) { }
		/*
		template<>
		MaterialAttribData<float, M>() : type_(UniformPrimitive::FLOAT), size_(M) { }

		template<>
		MaterialAttribData<int, M>() : type_(UniformPrimitive::INT), size_(M) { }
		*/
		T values[M];
	};

	class Material
	{
	public:
		Material(Shader* shader);
		virtual ~Material();

		std::unordered_map<std::string, MaterialAttrib> attributes;
		Shader* shader_;
	};
}

#endif // !BF_GRAPHICS_MATERIAL

