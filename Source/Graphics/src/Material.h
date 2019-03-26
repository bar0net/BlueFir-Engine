#ifndef BF_GRAPHICS_MATERIAL
#define BF_GRAPHICS_MATERIAL

#include "BaseMacros.h"
#include <unordered_map>
#include <string>

#include "Uniform.h"
// TODO: We only need an enum class from Uniforms.h
// maybe we should separate the enums into a seperate .h

// TODO: Find a more elegant solution than to register
// Textures using 'void' type...

// TODO: Be [really]^2 sure that SetData is not accessing
// forbidden memory!

namespace bluefir::graphics
{
	class Shader;

	struct MaterialAttrib 
	{ 
	public:

		virtual ~MaterialAttrib() { if (data_) delete[] data_; }

		void SetData(const void* data) { ASSERT(data && sizeof(data) != size_); std::memcpy(data_, data, size_); }
		
		template <class T>
		T* GetData() const { return (T*)data_; }

		template <class T>
		T GetValue() const { return ((T*)data_)[0]; }

	public:
		UniformPrimitive type_ = UniformPrimitive::NONE;
		unsigned int count_ = 0;

	protected:
		unsigned int size_ = 0;
		void* data_ = nullptr;
	};

	template <class T, unsigned int M>
	struct MaterialAttribData : public MaterialAttrib
	{
		MaterialAttribData() { type_= UniformPrimitive::NONE; count_ = M; size_ = M * sizeof(T); data_ = new char[size_]; }
	};

	template <unsigned int M>
	struct MaterialAttribData<float, M> : public MaterialAttrib
	{
		MaterialAttribData() { type_ = UniformPrimitive::FLOAT; count_ = M; size_ = M * sizeof(float); data_ = new char[size_]; }
	};

	template <unsigned int M>
	struct MaterialAttribData<int, M> : public MaterialAttrib
	{
		MaterialAttribData() { type_ = UniformPrimitive::INT; count_ = M; size_ = M * sizeof(int); data_ = new char[size_]; }
	};

	template <unsigned int M>
	struct MaterialAttribData<void, M> : public MaterialAttrib
	{
		MaterialAttribData() { type_ = UniformPrimitive::TEXTURE; count_ = M; size_ = M * sizeof(int); data_ = new char[size_]; }
	};

	class Material
	{
	public:
		Material(): shader_(0) {}
		Material(int shader) : shader_(shader) {}
		virtual ~Material() { for (auto it = atributes_.begin(); it != atributes_.end(); ++it) delete it->second; atributes_.clear(); }

		std::unordered_map<std::string, MaterialAttrib*> atributes_;
		int shader_ = 0;
	};
}

#endif // !BF_GRAPHICS_MATERIAL

