#include <math.h>
#include <gtc/matrix_transform.hpp>
#include "FreeCamera.h"


FreeCamera::FreeCamera(Keyboard& keyboard) : keyboard(keyboard), pitch(0), yaw(0)
{
	position.x = position.y = position.z = 0;
}

void FreeCamera::Update(Time t)
{
	float dt = static_cast<float>(t.dt) * 30;

	if (keyboard.IsKeyDown(GLFW_KEY_W))
	{
		position.x += dt * sinf(yaw);
		position.y -= dt * sinf(pitch);
		position.z -= dt * cosf(yaw);
	}
	if (keyboard.IsKeyDown(GLFW_KEY_S))
	{
		position.x -= dt * sinf(yaw);
		position.y += dt * sinf(pitch);
		position.z += dt * cosf(yaw);
	}
	if (keyboard.IsKeyDown(GLFW_KEY_A))
	{
		position.x -= dt * cosf(yaw);
		position.z -= dt * sinf(yaw);
	}
	if (keyboard.IsKeyDown(GLFW_KEY_D))
	{
		position.x += dt * cosf(yaw);
		position.z += dt * sinf(yaw);
	}
	if (keyboard.IsKeyDown(GLFW_KEY_SPACE))
	{
		position.y += dt * 1;
	}
	if (keyboard.IsKeyDown(GLFW_KEY_Z))
	{
		position.y -= dt * 1;
	}
	if (keyboard.IsKeyDown(GLFW_KEY_H))
	{
		//position.x = 0;
		//position.y = 264;
		//position.z = 100;
		position.x = 184;
		position.y = 336;
		position.z = 88;
	}
	if (keyboard.IsKeyDown(GLFW_KEY_LEFT))
	{
		yaw -= 1 * dt;
	}
	if (keyboard.IsKeyDown(GLFW_KEY_RIGHT))
	{
		yaw += 1 * dt;
	}

	glm::mat4x4 rotateMatrix = glm::rotate(glm::mat4(1.0f), yaw, glm::vec3(0, 1, 0)) *
		glm::rotate(glm::mat4(1.0f), pitch, glm::vec3(1, 0, 0));
	glm::mat4x4 translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-position.x, -position.y, -position.z));
	viewMatrix = rotateMatrix * translateMatrix;
}