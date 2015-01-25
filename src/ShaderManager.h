#ifndef _SHADER_MANAGER_H_
#define _SHADER_MANAGER_H_

#include <mat4x4.hpp>
#include <map>

enum class ShaderUniformConsts
{
	PROJECTION_MATRIX,
	VIEW_MATRIX,

	LIGHTMAP_SAMPLER,

};

enum ShaderProgs
{
	DEFAULT = 0,
	MAX_SHADER_PROGS
};

struct ShaderProgram
{
	int programId, vertexId, fragmentId;
	std::map<ShaderUniformConsts, GLuint> uniformLocations;
};

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();

	bool LoadDefaultShaders();

	void UseProgram(ShaderProgs program);

	template<typename T>
	void BindUniformData(ShaderUniformConsts type, const T data)
	{
		const ShaderProgram& prog = programs[activeProgram];
		auto typeIt = prog.uniformLocations.find(type);
		if (typeIt != prog.uniformLocations.end())
		{
			GLuint loc = typeIt->second;
			BindUniform(loc, data);
		}
	}

private:
	ShaderProgram programs[ShaderProgs::MAX_SHADER_PROGS];
	ShaderProgs activeProgram;

	void BindUniform(GLuint loc, const glm::mat4x4& mat);
	void BindUniform(GLuint loc, const GLuint value);
};

#endif
