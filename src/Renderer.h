#ifndef RENDERER_H_
#define RENDERER_H_

#include <GLFW/glfw3.h>
#include "Common.h"

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
};

#endif