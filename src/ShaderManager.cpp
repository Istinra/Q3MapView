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

void ShaderManager::LoadDefaultShaders()
{
	const char *vertexShaderSource =
		"#version 330 core"

		"precision highp float;"

		"uniform mat4 projectionMatrix;"
		"uniform mat4 modelviewMatrix;"

		"in vec3 position; "

		"out vec4 pos;"

		"void main(void)"
		"{"
			"gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1);"
			"pos = vec4(position, 1);"
		"}; ";

	const char * const fragmentShaderSource =
		"#version 330 core"

		"precision highp float;"

		"uniform vec4 boxColour;"

		"in vec4 pos;"

		"out vec4 fragColour;"

		"void main(void)"
		"{"
			"fragColour = pos;//boxColour;"
		"}";

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
}

void ShaderManager::UseProgram(ShaderProgs program)
{
	if (program != activeProgram)
	{
		activeProgram = program;
		glUseProgram(programs[program].programId);
	}
}