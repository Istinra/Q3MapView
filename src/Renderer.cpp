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
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void Renderer::InitGl(GLFWwindow* window)
{
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / static_cast<float>(height);
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	projection = glm::perspective(0.785398163f, ratio, 0.001f, 1000000.0f);
	
	shaderManager.LoadDefaultShaders();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bsp.IndiceCount() * sizeof(int), bsp.Indices(), GL_STATIC_DRAW);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, bsp.VertCount() * sizeof(BSPVertex), bsp.Verts(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(BSPVertex), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(BSPVertex), (void *) (3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(BSPVertex), (void *) (5 * sizeof(float)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(BSPVertex), (void *) (7 * sizeof(float)));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_BYTE, GL_FALSE, sizeof(BSPVertex), (void *) (10 * sizeof(float)));

	BSPVertex points[3];
	points[0].pos.x = 0;
	points[0].pos.y = 0.5f;
	points[0].pos.z = -1;

	points[1].pos.x = 0.5f;
	points[1].pos.y = -0.5f;
	points[1].pos.z = -1;

	points[2].pos.x = -0.5f;
	points[2].pos.y = -0.5f;
	points[2].pos.z = -1;

	glGenBuffers(1, &vbo2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao2);
	glBindVertexArray(vao2);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(BSPVertex), 0);

}

void Renderer::Render(const Time time)
{
	camera.Update(time);
	glViewport(0, 0, width, height);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	shaderManager.UseProgram(DEFAULT);
	shaderManager.BindMatiricies(projection, camera.ViewMatrix());

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glBindVertexArray(vao);

	BSPFace const * faces = bsp.Faces();
	int const * indices = bsp.Indices();
	for (int i = 0; i < bsp.FaceCount(); i++)
	{
		glDrawElementsBaseVertex(GL_TRIANGLES, faces->numIndices, GL_UNSIGNED_INT, 
			(void*) (faces->startIndex * sizeof(int)), faces->startVertIndex);
		++faces;
	}

	glBindVertexArray(vao2);
	glDrawArrays(GL_TRIANGLES, 0, 3);

}