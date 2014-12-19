#include <GLFW/glfw3.h>
#include <fstream>
#include "Quake3BSP.h"

std::fstream fs;

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void ErrorCallback(int error, const char* description)
{
	fs << "Error code << " << error << " " << description << std::endl;
}
int main() {

//	Quake3Bsp bsp;
//	bsp.LoadFromFile(std::string("C:\\Users\\Samuel\\Documents\\Q3MapView\\test-res\\maps\\Level.bsp"));

	fs.open("glfw.log", std::fstream::out | std::fstream::app);

	if (!glfwInit()) 
		exit(EXIT_FAILURE);
	glfwSetErrorCallback(ErrorCallback);

	GLFWwindow* window = glfwCreateWindow(640, 480, "Q3MapView", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetKeyCallback(window, KeyCallback);
	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window))
	{
		//Update


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	fs.close();

    return 0;
}
