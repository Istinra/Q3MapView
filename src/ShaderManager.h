#ifndef _SHADER_MANAGER_H_
#define _SHADER_MANAGER_H_

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

	void LoadDefaultShaders();

	void UseProgram(ShaderProgs program);

private:
	ShaderProgram programs[MAX_SHADER_PROGS];
	ShaderProgs activeProgram;
};

#endif
