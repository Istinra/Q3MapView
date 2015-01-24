#include <vector>
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

		"in vec3 pos;\n"
		"in vec2 texCoords;\n"
		"in vec2 lightCoords;\n"
		"in vec3 normal;\n"
		"in uint colour;\n"

		"out vec2 v_TexCoordinate;"

		"void main()\n"
		"{\n"
			"gl_Position = projectionMatrix * modelviewMatrix * vec4(pos, 1);\n"
			"v_TexCoordinate = lightCoords;"
		"};\n";

	const char* fragmentShaderSource =
		"#version 400\n"

		"uniform sampler2D lmSampler;\n"

		"in vec2 v_TexCoordinate;\n"

		"out vec4 frag_colour;\n"

		"void main () {\n"
		"  frag_colour = texture2D(lmSampler, v_TexCoordinate);\n"
		"}\n";

	ShaderProgram& defaultShader = programs[DEFAULT];
	defaultShader.vertexId = glCreateShader(GL_VERTEX_SHADER);
	defaultShader.fragmentId = glCreateShader(GL_FRAGMENT_SHADER);

	int status;

	glShaderSource(defaultShader.vertexId, 1, &vertexShaderSource, nullptr);
	glShaderSource(defaultShader.fragmentId, 1, &fragmentShaderSource, nullptr);

	glCompileShader(defaultShader.vertexId);

	glGetShaderiv(defaultShader.vertexId, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(defaultShader.vertexId, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(defaultShader.vertexId, maxLength, &maxLength, &infoLog[0]);
		std::string s = std::string(&infoLog[0], maxLength);
		return false;
	}

	glCompileShader(defaultShader.fragmentId);

	glGetShaderiv(defaultShader.fragmentId, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(defaultShader.fragmentId, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(defaultShader.fragmentId, maxLength, &maxLength, &infoLog[0]);
		std::string s = std::string(&infoLog[0], maxLength);
		return false;
	}

	defaultShader.programId = glCreateProgram();
	glAttachShader(defaultShader.programId, defaultShader.vertexId);
	glAttachShader(defaultShader.programId, defaultShader.fragmentId);
	
	glBindAttribLocation(defaultShader.programId, 0, "pos");
	glBindAttribLocation(defaultShader.programId, 1, "texCoords");
	glBindAttribLocation(defaultShader.programId, 2, "lightCoords");
	glBindAttribLocation(defaultShader.programId, 3, "normal");
	glBindAttribLocation(defaultShader.programId, 4, "colour");
	
	glLinkProgram(defaultShader.programId);

	int lightmapId = glGetUniformLocation(defaultShader.programId, "lmSampler");
	glUniform1i(lightmapId, 0);
	
	glGetProgramiv(defaultShader.programId, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(defaultShader.programId, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(defaultShader.programId, maxLength, &maxLength, &infoLog[0]);
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
