#include <cmath>

#include "headers/PlayerShip.h"


PlayerShip::PlayerShip() : thrusterForce(100)
{
}


PlayerShip::~PlayerShip()
{
}

void PlayerShip::handleKeyboard()
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_SPACE])
	{
		//give force values based on angle of ship
		forceX = thrusterForce * cos(angle * 3.14159265 / 180.0);
		forceY = thrusterForce * sin(angle * 3.14159265 / 180.0);
	}
	if (!state[SDL_SCANCODE_SPACE])
	{
		forceX = 0;
		forceY = 0;
	}
	if (state[SDL_SCANCODE_Q])
	{
		angle -= 1;
	}
	if (state[SDL_SCANCODE_E])
	{
		angle += 1;
	}
}