#include <math.h>
#include <gtc/matrix_transform.hpp>
#include "FreeCamera.h"


FreeCamera::FreeCamera(Keyboard& keyboard) : keyboard(keyboard), pitch(0), yaw(0)
{
	position.x = position.y = position.z = 0;
}

void FreeCamera::Update(Time t)
{
	if (keyboard.IsKeyDown(GLFW_KEY_W))
	{
		position.x += sinf(yaw);
		position.y -= sinf(pitch);
		position.z -= 0.0005f;//cosf(yaw);
	}
	if (keyboard.IsKeyDown(GLFW_KEY_S))
	{
		position.x -= sinf(yaw);
		position.y += sinf(pitch);
		position.z += 0.0005f;//cosf(yaw);
	}
	if (keyboard.IsKeyDown(GLFW_KEY_A))
	{
		position.x -= cosf(yaw);
		position.z -= sinf(yaw);
	}
	if (keyboard.IsKeyDown(GLFW_KEY_D))
	{
		position.x += cosf(yaw);
		position.z += sinf(yaw);
	}
	if (keyboard.IsKeyDown(GLFW_KEY_SPACE))
	{
		position.y += 1;
	}
	if (keyboard.IsKeyDown(GLFW_KEY_Z))
	{
		position.z += 1;
	}
	glm::mat4x4 rotateMatrix = glm::rotate(glm::mat4(1.0f), yaw, glm::vec3(0, 1, 0)) *
		glm::rotate(glm::mat4(1.0f), pitch, glm::vec3(1, 0, 0));
	glm::mat4x4 translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-position.x, -position.y, -position.z));
	viewMatrix = translateMatrix;
}