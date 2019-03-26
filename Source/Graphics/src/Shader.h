#ifndef BF_GRAPHICS_SHADER
#define BF_GRAPHICS_SHADER

#define BF_UNIFORM_NAME_LENGTH 16

#include <unordered_map>
#include <string>
#include <vector>

// TODO: Implement Uniform Class to manage uniforms


namespace bluefir::graphics
{
	class UniformBuffer;
	class Uniform;

	static unsigned int active_shader = 0;

	class Shader
	{
	public:
		Shader(const char* vertex_file, const char* fragment_file);
		virtual ~Shader();

		void Bind() const;
		void UnBind() const;

		bool SetUniform(std::string name, const void* data);

	private:
		void ParseUniforms();
		void ParseUniformBlocks();

		void RegisterUniform(const char* name, int type, int location, int size, unsigned int count);
		void RegisterUniformBlock(const char* name, int type, int location, int size, unsigned int count, unsigned int offset, const UniformBuffer* ubo);


		static unsigned int CompileShader(const char * text, int type);

	public:
		bool valid = false;

	private:
		unsigned int program_ = 0;
		std::unordered_map<std::string, Uniform*> uniforms_;
		std::vector<UniformBuffer*> uniform_buffers_;
	};
}

#endif // !BF_GRAPHICS_SHADER

