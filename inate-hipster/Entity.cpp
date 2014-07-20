#include "Entity.h"


Entity::Entity() : 
	body(NULL)
{
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(20.0f, 20.0f);
	bodyDef.userData = this;
	
	fixtureDef.density = DEFAULT_DENSITY;
	fixtureDef.friction = DEFAULT_FRICTION;
	fixtureDef.shape = NULL;

}

Entity::~Entity()
{
	worldptr->DestroyBody(body);
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
	
	body = worldptr->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;

	if (fixtureDef.shape == NULL)
	{
		b2Vec2 widthAndHeight(screenToWorld(texture.getWidth()), screenToWorld(texture.getHeight()));
		widthAndHeight *= 0.5f;
		dynamicBox.SetAsBox(widthAndHeight.x, widthAndHeight.y, widthAndHeight, 0.0f);

		fixtureDef.shape = &dynamicBox;
	}

	body->CreateFixture(&fixtureDef);

	if (!body)
	{
		return false;
	}

	return true;
}

void Entity::render(SDL_Rect* camera, SDL_Rect* clip)
{
	texture.render(worldToScreen(body->GetPosition().x) - camera->x, worldToScreen(body->GetPosition().y) - camera->y, clip, radToDeg(body->GetAngle()));
}

void Entity::renderAABB(SDL_Rect* camera)
{
	SDL_Rect* hitbox = new SDL_Rect;

	b2Fixture* fixture = body->GetFixtureList();
	b2AABB aabb = fixture->GetAABB(0);
	
	b2Vec2 lowerBound = aabb.lowerBound;
	SDL_Point screenLowerBound =worldToScreen(lowerBound);
	hitbox->x = screenLowerBound.x - camera->x;
	hitbox->y = screenLowerBound.y - camera->y;

	b2Vec2 extents = aabb.GetExtents();
	SDL_Point screenExtents = worldToScreen(extents);
	hitbox->w = screenExtents.x * 2;
	hitbox->h = screenExtents.y * 2;

	SDL_RenderFillRect(renderer, hitbox);

	delete hitbox;
	fixture = NULL;
}

void Entity::setPos(b2Vec2 vec)
{
	body->SetTransform(vec, body->GetAngle());
}

void Entity::setPos(b2Vec2 vec, float angle)
{
	body->SetTransform(vec, angle);
}

void Entity::startContact()
{

}

void Entity::endContact()
{

}