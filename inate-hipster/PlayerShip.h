#pragma once

#include <cmath>
#include <Box2D\Box2D.h>

#include "Entity.h"

class PlayerShip :
	public Entity
{
public:
	PlayerShip();
	~PlayerShip();
	
	void handleKeyboard();

private:
	float thrusterForce = 0.5f;
	float thrusterTorque = 1.0f;

	SDL_Rect* camera;
};

