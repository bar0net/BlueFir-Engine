#ifndef BF_GRAPHICS_MODELS
#define BF_GRAPHICS_MODELS

#include <vector>

namespace bluefir::graphics
{
	class VertexBuffer;
	class IndexBuffer;
	class VertexArray;
	class BufferLayout;

	enum class MeshType { POINT, LINE, TRIANGLE };

	class Mesh
	{
	public:
		Mesh(const std::vector<float>* vertices, const std::vector<unsigned int>* indices, const BufferLayout* layout);
		Mesh(const std::vector<float>* vertices, const std::vector<unsigned int>* indices, const BufferLayout* layout, MeshType type);
		virtual ~Mesh();

		void Build();
		void Bind() const;
		void UnBind() const;

	public:
		const std::vector<float>* vertices_;
		const std::vector<unsigned int>* indices_;
		const BufferLayout* layout_;
		MeshType type_ = MeshType::TRIANGLE;

	private:
		VertexBuffer* vbo_ = nullptr;
		IndexBuffer* ibo_ = nullptr;
		VertexArray* vao_ = nullptr;

		//Material* material;
	};
}

#endif // !BF_GRAPHICS_MODELS

