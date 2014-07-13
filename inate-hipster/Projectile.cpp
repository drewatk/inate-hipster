#include "Projectile.h"

Projectile::Projectile(PlayerShip* ship)
{
	bodyDef.bullet = true;
	
	b2Transform transform = ship->body->GetTransform();
	bodyDef.position = transform.p;
	bodyDef.angle = transform.q.GetAngle();
	
	b2Vec2 linvel = ship->body->GetLinearVelocity();
	bodyDef.linearVelocity = linvel;
	bodyDef.angularVelocity = ship->body->GetAngularVelocity();

}


Projectile::~Projectile()
{
}

ProjectileHandler::ProjectileHandler() :
curr(0)
{
	for (int i = 0; i < MAX_PROJECTILES; i++)
		projectiles[i] = NULL;
}

ProjectileHandler::~ProjectileHandler()
{
}

void ProjectileHandler::shoot(PlayerShip* ship, SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_f)
	{
		Projectile* newRocket = new Projectile(ship);
		newRocket->load("sprites/rocket.png");

		b2Vec2 force;
		force.x = 1000 * cos(ship->body->GetAngle());
		force.y = 1000 * sin(ship->body->GetAngle());
		newRocket->body->ApplyForceToCenter(force, true);

		if (curr >= MAX_PROJECTILES)
		{
			curr = 0;
		}
		delete projectiles[curr];
		projectiles[curr] = newRocket;
		curr++;
	}
}


void ProjectileHandler::render(SDL_Rect* camera)
{
	for (int i = 0; i < MAX_PROJECTILES; i++)
		if(projectiles[i] != NULL)
			projectiles[i]->render(camera);
}
