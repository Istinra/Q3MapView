#include "glew.h"
#include <GLFW/glfw3.h>
#include <gtc/matrix_transform.hpp>
#include <string>
#include "Renderer.h"

Renderer::Renderer(Keyboard& keyboard) : width(0), height(0), ratio(0), camera(keyboard)
{
	bsp.LoadFromFile(std::string("C:\\Users\\Samuel\\Documents\\Q3MapView\\test-res\\maps\\Level.bsp"));
}

Renderer::~Renderer()
{
}

void Renderer::InitGl(GLFWwindow* window)
{
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / static_cast<float>(height);
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	projection = glm::perspective(0.785398163f, ratio, 0.1f, 1000.0f);
	
	shaderManager.LoadDefaultShaders();



	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, bsp.VertCount() * sizeof (BSPVertex), bsp.Verts(), GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(BSPVertex), 0);
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(BSPVertex), (void *) (3 * sizeof(float)));
	//glEnableVertexAttribArray(2);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(BSPVertex), (void *) (6 * sizeof(float)));
	//glEnableVertexAttribArray(3);
	//glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(BSPVertex), (void *) (8 * sizeof(float)));
	//glEnableVertexAttribArray(4);
	//glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(BSPVertex), (void *) (10 * sizeof(float)));

	//float points[] = {
	//	0.0f, 0.5f, -1.0f,
	//	0.5f, -0.5f, -1.0f,
	//	-0.5f, -0.5f, -1.0f
	//};

	//glGenBuffers(1, &vbo);
	//glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, 9 * sizeof (float), points, GL_STATIC_DRAW);

	//glGenVertexArrays(1, &vao);
	//glBindVertexArray(vao);
	//glEnableVertexAttribArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

}

void Renderer::Render(const Time time)
{
	camera.Update(time);
	glViewport(0, 0, width, height);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	shaderManager.UseProgram(DEFAULT);
	shaderManager.BindMatiricies(projection, camera.ViewMatrix());

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, bsp.VertCount());

}