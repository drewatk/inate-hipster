#include "Entity.h"


Entity::Entity()
{
}

Entity::~Entity()
{
	body = NULL;
	texture.free();
}

//Loads an image from path into a texture and a dynamic body/fixture combo and calculates AABB
bool Entity::load(std::string path)
{
	if (!texture.loadFromFile(path))
	{
		return false;
	}
	
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 0.0f);
	body = worldptr->CreateBody(&bodyDef);
	
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(screenToWorld(texture.getWidth()) / 2, screenToWorld(texture.getHeight()) / 2);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = DEFAULT_DENSITY;
	fixtureDef.friction = DEFAULT_FRICTION;
	body->CreateFixture(&fixtureDef);

	if (!body)
	{
		return false;
	}

	return true;
}

void Entity::render(SDL_Rect* clip)
{
	texture.render(worldToScreen(body->GetPosition()), clip, (double)body->GetAngle());	
}



