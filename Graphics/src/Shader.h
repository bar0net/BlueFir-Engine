#ifndef BF_GRAPHICS_SHADER
#define BF_GRAPHICS_SHADER

// TODO: Define this class

namespace bluefir
{
	static unsigned int active_shader = 0;

	class Shader
	{
	public:
		Shader();
		~Shader();

		void Bind() const;
		void UnBind() const;

	private:
		unsigned int programID = 0;
	};
}

#endif // !BF_GRAPHICS_SHADER

