#pragma once
#include "headers\Sprite.h"
class PlayerShip :
	public Sprite
{
public:
	PlayerShip();
	~PlayerShip();

	void handleKeyboard();

private:
	int thrusterForce;
};



