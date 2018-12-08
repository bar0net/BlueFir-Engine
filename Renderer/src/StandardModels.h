#ifndef BR_GRAPHICS_STANDARDMODELS
#define BR_GRAPHICS_STANDARDMODELS

namespace bluefir::graphics
{
	class Mesh;

	enum class ModelList
	{
		Triangle = 0,
		Quad,
		Cube
	};

	class StandardModels
	{
	public:
		static Mesh* Get(ModelList type);

	private:
		StandardModels() = delete;

		static Mesh* Triangle();
		static Mesh* Quad();
		static Mesh* Cube();
	};
}

#endif // !BR_GRAPHICS_STANDARDMODELS

