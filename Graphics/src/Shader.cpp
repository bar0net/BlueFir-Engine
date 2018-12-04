#include "Shader.h"

#include <vector>
#include "GL/glew.h"

#include "Graphics.h"
#include "LogSystem.h"
#include "Buffer/UniformBuffer.h"

#include "Uniform.h"
#include "Uniforms/Uniform1.h"
#include "Uniforms/Uniform2.h"
#include "Uniforms/Uniform3.h"
#include "Uniforms/Uniform4.h"
#include "Uniforms/Uniform4x4.h"
#include "Uniforms/UniformBlock.h"


bluefir::graphics::Shader::Shader(const char * vertex_shader, const char * fragment_shader)
{
	ASSERT(vertex_shader && fragment_shader);

	// Build Shader
	unsigned int vertex_id = CompileShader(vertex_shader, (int)GL_VERTEX_SHADER);
	unsigned int fragment_id = CompileShader(fragment_shader, (int)GL_FRAGMENT_SHADER);

	if (vertex_id == 0 || fragment_id == 0)	LOGERROR("Shader could not compile.");
	else
	{
		program_ = glCreateProgram();
		GLCall(glAttachShader(program_, vertex_id));
		GLCall(glAttachShader(program_, fragment_id));
		GLCall(glLinkProgram(program_));

		int success = 0;
		glGetProgramiv(program_, GL_LINK_STATUS, &success);

		if (success == GL_FALSE)
		{
			LOGERROR("Program failed to link.");
		}
		else LOGINFO("Program successfully linked.");

		GLCall(glDetachShader(program_, vertex_id));
		GLCall(glDetachShader(program_, fragment_id));
		
		// Parse Uniforms in Shader and populate uniforms_ attribute.
		ParseUniforms();
		ParseUniformBlocks();
	}

	if (vertex_id != 0) GLCall(glDeleteShader(vertex_id));
	if (fragment_id != 0) GLCall(glDeleteShader(fragment_id));


#if(BF_DEBUG)
	// Show the contents of the uniforms_ attribute for debugging purpouses.
	for (auto it = uniforms_.begin(); it != uniforms_.end(); ++it)
	{
		if (it->second->block_)	LOGDEBUG("[BLOCK] name: %s | location: %i | size: %i" , it->first.c_str(), it->second->location_, it->second->size_);
		else LOGDEBUG("[UNFRM] name: %s | location: %i", it->first.c_str(), it->second->location_);
	}
#endif
}

bluefir::graphics::Shader::~Shader()
{
	if (active_shader == program_)
	{
		GLCall(glUseProgram(0));
		active_shader = 0;
	}

	// Delete UniformBlock buffers
	for (auto it = uniform_buffers_.begin(); it != uniform_buffers_.end(); ++it)
		delete *it;
	uniform_buffers_.clear();

	// Delete Uniforms from Map
	for (auto it = uniforms_.begin(); it != uniforms_.end(); ++it)
		delete it->second;

	uniforms_.clear();

	// Delete program
	GLCall(glDeleteProgram(program_));
}

void bluefir::graphics::Shader::Bind() const
{
	if (active_shader == program_) return;

	GLCall(glUseProgram(program_));
	active_shader = program_;
}

void bluefir::graphics::Shader::UnBind() const
{
	if (active_shader != program_) return;

	GLCall(glUseProgram(0));
	active_shader = 0;
}

void bluefir::graphics::Shader::ParseUniforms()
{
	GLint i, count, size;
	GLenum type;
	GLsizei length;

	char name[BF_UNIFORM_NAME_LENGTH];

	GLCall(glGetProgramiv(program_, GL_ACTIVE_UNIFORMS, &count));
	for (i = 0; i < count; i++)
	{
		GLCall(glGetActiveUniform(program_, (GLuint)i, BF_UNIFORM_NAME_LENGTH, &length, &size, &type, name));
		GLCall(int location = glGetUniformLocation(program_, name));
		// TODO: Check if "size" is needed. 
		// TODO: Implement Uniform Arrays (count > 1)... (maybe register each element of the array
		// as a different uniform?)
		if (location != -1) this->RegisterUniform(name, type, location, size, count);
	}
}

void bluefir::graphics::Shader::ParseUniformBlocks()
{
	GLint count, length;
	char name[BF_UNIFORM_NAME_LENGTH];
	GLCall(glGetProgramiv(program_, GL_ACTIVE_UNIFORM_BLOCKS, &count));

	// Check every uniform block
	for (int i = 0; i < count; ++i)
	{
		// Get the number of uniforms in the block and the total byte-size of the block
		int elements;
		int size;
		GLCall(glGetActiveUniformBlockiv(program_, i, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &elements));
		GLCall(glGetActiveUniformBlockiv(program_, i, GL_UNIFORM_BLOCK_DATA_SIZE, &size));
		uniform_buffers_.push_back(new UniformBuffer(size));

		// Get attribs for every uniform in the block
		GLuint* indices = new GLuint[elements];
		GLint* offsets = new GLint[elements];
		GLsizei* types = new GLsizei[elements];
		GLsizei* sizes = new GLsizei[elements];
		GLCall(glGetActiveUniformBlockiv(program_, i, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, (GLint*)indices));
		GLCall(glGetActiveUniformsiv(program_, elements, indices, GL_UNIFORM_OFFSET, offsets));
		GLCall(glGetActiveUniformsiv(program_, elements, indices, GL_UNIFORM_TYPE, types));
		GLCall(glGetActiveUniformsiv(program_, elements, indices, GL_UNIFORM_SIZE, sizes));

		// Parse every uniform in the block
		for (int j = 0; j < elements - 1; ++j)
		{
			GLCall(glGetActiveUniformName(program_, indices[j], BF_UNIFORM_NAME_LENGTH, &length, name));
			RegisterUniformBlock(name, types[j], i, offsets[j + 1] - offsets[j], sizes[j], offsets[j], uniform_buffers_.back());
		}
		GLCall(glGetActiveUniformName(program_, indices[elements - 1], BF_UNIFORM_NAME_LENGTH, &length, name));
		RegisterUniformBlock(name, types[elements - 1], i, size - offsets[elements - 1], sizes[elements - 1], offsets[elements - 1], uniform_buffers_.back());

		// Bind Block
		GLCall(glUniformBlockBinding(program_, i, i));
		
		// Delete all allocated pointers
		delete[] indices; indices = nullptr;
		delete[] offsets; offsets = nullptr;
		delete[] types; types = nullptr;
		delete[] sizes; sizes = nullptr;
	}
}

void bluefir::graphics::Shader::RegisterUniform(const char* name, int type, int location, int size, unsigned int count)
{
	ASSERT(name);

	switch (type)
	{
	case(GL_FLOAT):
		uniforms_[std::string(name)] = new Uniform1<float>(location, size, count);
		break;

	case (GL_FLOAT_VEC2):
		uniforms_[std::string(name)] = new Uniform2<float>(location, size, count);
		break;

	case (GL_FLOAT_VEC3):
		uniforms_[std::string(name)] = new Uniform3<float>(location, size, count);
		break;

	case (GL_FLOAT_VEC4):
		uniforms_[std::string(name)] = new Uniform4<float>(location, size, count);
		break;

	case (GL_FLOAT_MAT4):
		uniforms_[std::string(name)] = new Uniform4x4<float>(location, size, count);
		break;

	default:
		LOGERROR("Unsupported type for uniform %s (type: %i)", name, type);
		break;
	}

}

void bluefir::graphics::Shader::RegisterUniformBlock(const char * name, int type, int location, int size, unsigned int count, unsigned int offset, const UniformBuffer * ubo)
{
	ASSERT(name);

	switch (type)
	{
	case (GL_FLOAT_VEC4):
		uniforms_[std::string(name)] = new UniformBlock<float>(location, offset, size, count, ubo, UniformType::VEC4);
		break;

	case(GL_FLOAT_MAT4):
		uniforms_[std::string(name)] = new UniformBlock<float>(location, offset, size, count, ubo, UniformType::MAT4);
		break;

	default:
		LOGERROR("Unsupported type for uniform %s (type: %i)", name, type);
		break;
	}
}

bool bluefir::graphics::Shader::SetUniform(std::string name, const void * data)
{
	if (uniforms_.find(name) == uniforms_.end()) return false;

	Bind();
	uniforms_[name]->Set(data);
	return true;
}

unsigned int bluefir::graphics::Shader::CompileShader(const char * text, int type)
{
	ASSERT(text);
	int success = 0;

	GLCall(unsigned int shader = glCreateShader((GLenum)type));
	GLCall(glShaderSource(shader, 1, &text, NULL));
	GLCall(glCompileShader(shader));
	GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		GLCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength));

		std::vector<GLchar> infoLog(maxLength);
		GLCall(glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]));

		const char* msg = infoLog.data();
		LOGERROR("Could not compile shader. << %s >>", msg);
		return 0U;
	}
	else LOGINFO("Shader compiled successfully");
	
	return shader;
}
