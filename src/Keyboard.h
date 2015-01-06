#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <GLFW/glfw3.h>

class Keyboard
{
public:
	Keyboard();

	void KeyDown(int key)
	{
		keyStates[key] = true;
	}

	void KeyUp(int key)
	{
		keyStates[key] = false;
	}

	bool IsKeyDown(int key)
	{
		return keyStates[key];
	}

private:
	bool keyStates[GLFW_KEY_LAST];
};

#endif