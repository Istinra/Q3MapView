#ifndef _FREE_CAMERA_H_
#define _FREE_CAMERA_H_

#include <mat4x4.hpp>
#include "Keyboard.h"
#include "BSPTypes.h"

class FreeCamera
{
public :
	explicit FreeCamera(Keyboard& keyboard);

	void Update(Time t);

	const glm::mat4x4& ViewMatrix() const { return viewMatrix; }

	Vec3 Position() const { return position; }

private:
	Keyboard& keyboard;
	Vec3 position;
	float pitch, yaw;
	glm::mat4x4 viewMatrix;
};

#endif