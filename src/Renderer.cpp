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
	glDeleteSamplers(1, &sampler);
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
	CreateTextures();

	const byte* imageBits = reinterpret_cast<const byte*>(bsp.LightMaps()->imageData);
	lightmaps.emplace_back(0, 128, 128, imageBits);

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
	shaderManager.BindUniformData(ShaderUniformConsts::PROJECTION_MATRIX, projection);
	shaderManager.BindUniformData(ShaderUniformConsts::VIEW_MATRIX, camera.ViewMatrix());
	shaderManager.BindUniformData<GLuint>(ShaderUniformConsts::LIGHTMAP_SAMPLER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glBindVertexArray(vao);

	glActiveTexture(GL_TEXTURE0 + 0);
	Texture& lightMap = lightmaps.at(0);
	glBindSampler(0, sampler);

	const BSPLeaf& currentLeaf = bsp.FindLeaf(camera.Position());
	const BSPLeaf* leaves = bsp.Leaves();
	const BSPFace* faces = bsp.Faces();
	const int* leafFaces = bsp.LeafFaces();

	for (int i = 0; i < bsp.LeafCount(); ++i)
	{
		const BSPLeaf& targetLeaf = leaves[i];
		
		if (bsp.IsLeafVisible(currentLeaf.visData, targetLeaf.visData))
		{
			for (int j = 0; j < targetLeaf.numLeafFace; ++j)
			{
				int faceIndex = leafFaces[targetLeaf.firstLeafFace + j];
				const BSPFace* face = &faces[faceIndex];
				if (face->type == POLYGON)
				{
					glDrawElementsBaseVertex(GL_TRIANGLES, face->numIndices, GL_UNSIGNED_INT,
						reinterpret_cast<void *>(face->startIndex * sizeof(int)), face->startVertIndex);
				}
			}
		}

	}	
}

void Renderer::CreateTextures()
{
	const TextureData* data = bsp.TexeData();
	int numTextures = bsp.TextureCount();
	for (int i = 0; i < numTextures; ++i)
	{
		textures.emplace_back(i, data[i].width, data[i].height, data[i].data.get());
	}
	bsp.CleanUpTextures();
}
