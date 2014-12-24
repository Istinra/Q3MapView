#ifndef _SHADER_H_
#define _SHADER_H_


class Shader
{
public:
	Shader(int vertexId, int fragmentId, int programId);
	~Shader();

private:
	int vertexId, fragmentId, programId;
};

#endif