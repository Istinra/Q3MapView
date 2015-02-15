#ifndef RENDERER_H_
#define RENDERER_H_

#include <GLFW/glfw3.h>
#include <mat4x4.hpp>
#include "FreeCamera.h"
#include "Texture.h"
#include "Common.h"
#include "ShaderManager.h"
#include "Quake3BSP.h"
#include <vector>

class Renderer
{
public:
	explicit Renderer(Keyboard& keyboard);
	~Renderer();

	void InitGl(GLFWwindow* window);
	void Render(const Time time);

private:
	int width;
	int height;
	float ratio;

	ShaderManager shaderManager;
	FreeCamera camera;

	glm::mat4x4 projection;

	std::vector<Texture> textures;
	std::vector<Texture> lightmaps;

	Quake3Bsp bsp;
	unsigned int vao, vbo, ibo;
	unsigned int sampler;
};

#endif