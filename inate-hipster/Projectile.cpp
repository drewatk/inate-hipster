#include "Projectile.h"

Projectile::Projectile(PlayerShip* ship) : contacting(false)
{
	bodyDef.bullet = true;
	
	b2Transform transform = ship->body->GetTransform();
	bodyDef.position = transform.p;
	bodyDef.angle = transform.q.GetAngle();
	
	b2Vec2 linvel = ship->body->GetLinearVelocity();
	bodyDef.linearVelocity = linvel;
	bodyDef.angularVelocity = ship->body->GetAngularVelocity();

}

ProjectileHandler::ProjectileHandler() :
currRocket(0)
{
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		rockets1[i] = NULL;
		rockets2[i] = NULL;
	}
}

ProjectileHandler::~ProjectileHandler()
{
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		delete rockets1[i];
		rockets1[i] = NULL;
		delete rockets2[i];
		rockets2[i] = NULL;
	}
}

void ProjectileHandler::handleEvent(PlayerShip* ship, SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_f)
	{
		Rocket1* newRocket = new Rocket1(ship);
		newRocket->load("sprites/rocket.png");
		Rocket2* newRocket2 = new Rocket2(ship);
		newRocket2->load("sprites/rocket.png");

		b2Vec2 force;
		force.x = 1000 * cos(ship->body->GetAngle());
		force.y = 1000 * sin(ship->body->GetAngle());
		newRocket->body->ApplyForceToCenter(force, true);
		newRocket2->body->ApplyForceToCenter(force, true);

		if (currRocket >= MAX_PROJECTILES)
		{
			currRocket = 0;
		}
		delete rockets1[currRocket];
		delete rockets2[currRocket];
		rockets1[currRocket] = newRocket;
		rockets2[currRocket] = newRocket2;
		currRocket++;
	}
}


void ProjectileHandler::render(SDL_Rect* camera)
{
	for (int i = 0; i < MAX_PROJECTILES; i++)
		if (rockets1[i] != NULL)
		{
			rockets1[i]->render(camera);
			rockets2[i]->render(camera);
		}
}

Rocket2::Rocket2(PlayerShip* ship) :
Projectile(ship)
{
	b2Vec2 worldPoint(0.0f, 3.95f);
	bodyDef.position = ship->body->GetWorldPoint(worldPoint);
	
}

Rocket1::Rocket1(PlayerShip* ship) :
Projectile(ship)
{
	b2Vec2 worldPoint(0.0f, -0.55f);
	bodyDef.position = ship->body->GetWorldPoint(worldPoint);

}
