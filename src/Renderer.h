#ifndef RENDERER_H_
#define RENDERER_H_

#include <GLFW/glfw3.h>
#include "Common.h"
#include "ShaderManager.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void InitGl(GLFWwindow* window);
	void Render(const Time time);
	
private:
	int width;
	int height;
	float ratio;

	ShaderManager shaderManager;

	//Test remove me
	unsigned int vao, vbo;
};

#endif