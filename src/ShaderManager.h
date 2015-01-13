#ifndef _SHADER_MANAGER_H_
#define _SHADER_MANAGER_H_

#include <mat4x4.hpp>

enum ShaderUniformConstants
{
	MO = 0,

	MAX_UNIFORMCONSTS
};

enum ShaderProgs
{
	DEFAULT = 0,
	MAX_SHADER_PROGS
};

struct ShaderProgram
{
	int programId, vertexId, fragmentId;
};

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();

	bool LoadDefaultShaders();

	void UseProgram(ShaderProgs program);
	void BindMatiricies(const glm::mat4x4& proj, const glm::mat4x4& view);
	void BindTextures();
	void BindLightMapId(int id);

private:
	ShaderProgram programs[MAX_SHADER_PROGS];
	ShaderProgs activeProgram;
};

#endif
