#pragma once

#include "Entity.h"
#include "PlayerShip.h"

//max projectiles of one type
const int MAX_PROJECTILES = 100;

class Projectile :
	public Entity
{
protected:
	Projectile(PlayerShip* ship);
	
	friend class ProjectileHandler;
};

class ProjectileHandler
{
public: 
	ProjectileHandler();
	~ProjectileHandler();
	//shoots if player is pressing the key (f by default)
	void handleEvent(PlayerShip* ship, SDL_Event& e);

	//go through array and render each projectile
	void render(SDL_Rect* camera);

private:
	Projectile* rockets1[MAX_PROJECTILES];
	Projectile* rockets2[MAX_PROJECTILES];
	int currRocket;
};

class Rocket2 :
	public Projectile
{
private:
	Rocket2(PlayerShip* ship);
	friend class ProjectileHandler;
};

class Rocket1 :
	public Projectile
{
private:
	Rocket1(PlayerShip* ship);
	friend class ProjectileHandler;
};