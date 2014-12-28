#include "Keyboard.h"

Keyboard::Keyboard()
{
	for (bool& ks : keyStates)
	{
		ks = false;
	}
}