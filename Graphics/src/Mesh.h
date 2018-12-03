#ifndef BF_GRAPHICS_MODELS
#define BF_GRAPHICS_MODELS

#include <vector>

namespace bluefir::graphics
{
	class VertexBuffer;
	class IndexBuffer;
	class VertexArray;
	class BufferLayout;

	struct Mesh
	{
	public:
		Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const BufferLayout& layout);
		virtual ~Mesh();
		void Build();
		void Bind() const;
		void UnBind() const;

	public:
		std::vector<float> vertices_;
		std::vector<unsigned int> indices_;
		const BufferLayout* layout_;

	private:
		VertexBuffer* vbo_ = nullptr;
		IndexBuffer* ibo_ = nullptr;
		VertexArray* vao_ = nullptr;

		//Material* material;
	};

	static class StandardModels
	{
	public:
		static Mesh* Triangle();
		static Mesh* Cube();
	};
}

#endif // !BF_GRAPHICS_MODELS

