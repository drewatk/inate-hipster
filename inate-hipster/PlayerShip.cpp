#include "PlayerShip.h"


PlayerShip::PlayerShip()
{
	camera = new SDL_Rect;
	camera->x = 0;
	camera->y = 0;
	camera->w = SCREEN_WIDTH;
	camera->h = SCREEN_HEIGHT;

	bodyDef.angularDamping = 0.5f;
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

void PlayerShip::cameraMove()
{
	//Center the camera over the ship
	camera->x = (worldToScreen(body->GetPosition().x) + texture.getWidth() / 2) - SCREEN_WIDTH / 2;
	camera->y = (worldToScreen(body->GetPosition().y) + texture.getHeight() / 2) - SCREEN_HEIGHT / 2;

	//Keep the camera in bounds
	if (camera->x < 0)
	{
		camera->x = 0;
	}
	if (camera->y < 0)
	{
		camera->y = 0;
	}
	if (camera->x > LEVEL_WIDTH - camera->w)
	{
		camera->x = LEVEL_WIDTH - camera->w;
	}
	if (camera->y > LEVEL_HEIGHT - camera->h)
	{
		camera->y = LEVEL_HEIGHT - camera->h;
	}
}

SDL_Rect* PlayerShip::getCamera()
{
	return camera;
}

