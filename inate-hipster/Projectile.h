#pragma once

#include "Entity.h"
#include "PlayerShip.h"

//max projectiles of one type
const int MAX_PROJECTILES = 10;

class Projectile :
	public Entity
{
private:
	Projectile(PlayerShip* ship);
	friend class ProjectileHandler;
public:
	~Projectile();
};

class ProjectileHandler
{
public: 
	ProjectileHandler();
	~ProjectileHandler();
	//shoots if player is pressing the key (f by default), returns true if shot bullet
	void shoot(PlayerShip* ship, SDL_Event& e);

	//go through array and render each projectile
	void render(SDL_Rect* camera);

private:
	Projectile* projectiles[MAX_PROJECTILES];
	int curr;
};

