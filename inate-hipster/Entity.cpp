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
	bodyDef.position.Set(20.0f, 20.0f);
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
	texture.render(worldToScreen(body->GetPosition()), clip, radToDeg(body->GetAngle()));	
}

void Entity::renderHitbox()
{
	SDL_Rect* hitbox = new SDL_Rect;

	b2Fixture* fixture = body->GetFixtureList();
	b2AABB aabb = fixture->GetAABB(0);
	
	b2Vec2 lowerBound = aabb.lowerBound;
	SDL_Point screenLowerBound =worldToScreen(lowerBound);
	hitbox->x = screenLowerBound.x;
	hitbox->y = screenLowerBound.y;

	b2Vec2 extents = aabb.GetExtents();
	SDL_Point screenExtents = worldToScreen(extents);
	hitbox->w = screenExtents.x * 2;
	hitbox->h = screenExtents.y * 2;

	SDL_RenderFillRect(renderer, hitbox);

	delete hitbox;
}
