#include "glew.h"

#include "ShaderManager.h"

#include <GLFW/glfw3.h>
#include <fstream>

#include "Quake3BSP.h"
#include "Renderer.h"
#include "Keyboard.h"

std::fstream fs;
Keyboard* kb;

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	else if (action == GLFW_PRESS)
		kb->KeyDown(key);
	else if (action == GLFW_RELEASE)
		kb->KeyUp(key);
}

void ErrorCallback(int error, const char* description)
{
	fs << "Error code << " << error << " " << description << std::endl;
}

int main() {

	fs.open("glfw.log", std::fstream::out | std::fstream::app);

	if (!glfwInit()) 
		exit(EXIT_FAILURE);
	glfwSetErrorCallback(ErrorCallback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(640, 480, "Q3MapView", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		//glewGetErrorString(err)
		return -1;
	}

	Keyboard keyboard;
	kb = &keyboard;
	glfwSetKeyCallback(window, KeyCallback);

	Renderer renderer(keyboard);
	renderer.InitGl(window);

	Time time { 0 };

	while (!glfwWindowShouldClose(window))
	{
		double newTotal = glfwGetTime();
		time.dt = newTotal - time.total;
		time.total = newTotal;
		
		//Update
		renderer.Render(time);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	fs.close();

    return 0;
}
