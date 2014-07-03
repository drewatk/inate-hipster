#pragma once
#include "Sprite.h"

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



