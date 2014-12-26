#include "glew.h"
#include <GLFW/glfw3.h>
#include "ShaderManager.h"

#include <string>


ShaderManager::ShaderManager() : activeProgram(MAX_SHADER_PROGS)
{
	
}


ShaderManager::~ShaderManager()
{
	for (ShaderProgram& program : programs)
	{
		if (program.programId != 0)
		{
			glDetachShader(program.programId, program.vertexId);
			glDetachShader(program.programId, program.fragmentId);
			glDeleteShader(program.vertexId);
			glDeleteShader(program.vertexId);
			glDeleteProgram(program.programId);
		}
	}

}

bool ShaderManager::LoadDefaultShaders()
{
	const char *vertexShaderSource =
		"#version 330 core\n"

		"precision highp float;\n"

		"uniform mat4 projectionMatrix;\n"
		"uniform mat4 modelviewMatrix;\n"

		"in vec3 position;\n"

		"out vec4 pos;\n"

		"void main(void)\n"
		"{\n"
			"gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1);\n"
			"pos = vec4(position, 1);\n"
		"};\n";

	const char * const fragmentShaderSource =
		"#version 330 core\n"

		"precision highp float;\n"

		"uniform vec4 boxColour;\n"

		"in vec4 pos;\n"

		"out vec4 fragColour;\n"

		"void main(void)\n"
		"{\n"
			"fragColour = pos;//boxColour;\n"
		"}\n";

	ShaderProgram& defaultShader = programs[DEFAULT];
	defaultShader.vertexId = glCreateShader(GL_VERTEX_SHADER);
	defaultShader.fragmentId = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(defaultShader.vertexId, 1, &vertexShaderSource, nullptr);
	glShaderSource(defaultShader.fragmentId, 1, &fragmentShaderSource, nullptr);

	glCompileShader(defaultShader.vertexId);
	glCompileShader(defaultShader.fragmentId);

	defaultShader.programId = glCreateProgram();
	glAttachShader(defaultShader.programId, defaultShader.vertexId);
	glAttachShader(defaultShader.programId, defaultShader.fragmentId);
	
	glLinkProgram(defaultShader.programId);

	int status;
	glGetProgramiv(defaultShader.programId, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		return false;
	}
	return true;
}

void ShaderManager::UseProgram(ShaderProgs program)
{
	if (program != activeProgram)
	{
		activeProgram = program;
		glUseProgram(programs[program].programId);
	}
}