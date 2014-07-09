#include "PlayerShip.h"


PlayerShip::PlayerShip()
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
		b2Vec2 force;
		force.x = thrusterForce * cos(body->GetAngle());
		force.y = thrusterForce * sin(body->GetAngle());
		body->ApplyForceToCenter(force, true);
	}

	//set rotation acceleration based on q and e
	if (state[SDL_SCANCODE_Q])
	{
		body->ApplyTorque(thrusterTorque * -1, true);
	}
	else if (state[SDL_SCANCODE_E])
	{
		body->ApplyTorque(thrusterTorque, true);
	}
}