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
	else
	{
		forceX = 0;
		forceY = 0;
	}
	
	//set rotation acceleration based on q and e
	if (state[SDL_SCANCODE_Q])
		angVel = -50;
	else if (state[SDL_SCANCODE_E])
		angVel = 50;
	else
		angVel = 0;
}