#include "glew.h"
#include <GLFW/glfw3.h>
#include <gtc/type_ptr.hpp>
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
		"#version 400\n"

		"uniform mat4 projectionMatrix;\n"
		"uniform mat4 modelviewMatrix;\n"

		"in vec3 vp;\n"
		"out vec3 ex;\n"

		"void main()\n"
		"{\n"
			"gl_Position = projectionMatrix * modelviewMatrix * vec4(vp, 1);\n"
			"ex = vp;"
		"};\n";

	const char* fragmentShaderSource =
		"#version 400\n"

		"out vec4 frag_colour;"
		"in vec3 ex;"

		"void main () {"
		"  frag_colour = vec4 (ex.x > 0 ? 1 : 0, ex.y > 0 ? 1 : 0, ex.z > 0 ? 1 : 0, 1.0);"
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

void ShaderManager::BindMatiricies(const glm::mat4x4& proj, const glm::mat4x4& view)
{
	const ShaderProgram& prog = programs[activeProgram];
	int projLoc = glGetUniformLocation(prog.programId, "projectionMatrix");
	glUniformMatrix4fv(projLoc, 1, false, glm::value_ptr(proj));
	int vmLoc = glGetUniformLocation(prog.programId, "modelviewMatrix");
	glUniformMatrix4fv(vmLoc, 1, false, glm::value_ptr(view));
}
