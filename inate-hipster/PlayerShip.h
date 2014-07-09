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
	
	void cameraMove();
	SDL_Rect* getCamera();
	
	void render(SDL_Rect* clip = NULL);

	void handleKeyboard();

private:
	float thrusterForce = 100.0f;
	float thrusterTorque = 100.0f;

	SDL_Rect* camera;
};

