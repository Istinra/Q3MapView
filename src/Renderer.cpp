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
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void Renderer::InitGl(GLFWwindow* window)
{
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / static_cast<float>(height);
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);
	glClearColor(0.2f, 0.2f, 0.2f, 1);

	projection = glm::perspective(0.785398163f, ratio, 0.001f, 1000000.0f);
	
	shaderManager.LoadDefaultShaders();
	shaderManager.UseProgram(DEFAULT);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bsp.IndiceCount() * sizeof(int), bsp.Indices(), GL_STATIC_DRAW);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, bsp.VertCount() * sizeof(BSPVertex), bsp.Verts(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(BSPVertex), nullptr);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(BSPVertex), reinterpret_cast<void *>(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(BSPVertex), reinterpret_cast<void *>(5 * sizeof(float)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(BSPVertex), reinterpret_cast<void *>(7 * sizeof(float)));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_BYTE, GL_FALSE, sizeof(BSPVertex), reinterpret_cast<void *>(10 * sizeof(float)));

	//Textures
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &lightmapAlias);
	glBindTexture(GL_TEXTURE_2D, lightmapAlias);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	const byte *imageBits = reinterpret_cast<const byte*>(bsp.LightMaps()->imageData);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 128, 128, 0, GL_RGB, GL_UNSIGNED_BYTE, imageBits);

	glGenSamplers(1, &sampler);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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

	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, lightmapAlias);
	glBindSampler(0, sampler);

	BSPFace const * faces = bsp.Faces();
	int const * indices = bsp.Indices();
	for (int i = 0; i < bsp.FaceCount(); i++)
	{
		glDrawElementsBaseVertex(GL_TRIANGLES, faces->numIndices, GL_UNSIGNED_INT, 
			reinterpret_cast<void *>(faces->startIndex * sizeof(int)), faces->startVertIndex);
		++faces;
	}
}