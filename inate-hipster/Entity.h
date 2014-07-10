#pragma once

#include <Box2D\Box2D.h>
#include <SDL.h>
#include <string>

#include "screenConst.h"
#include "Texture.h"

const float DEFAULT_FRICTION = 0.3f;
const float DEFAULT_DENSITY = 1.0f;

class Entity
{
public:
	Entity();
	~Entity();
	
	bool load(std::string path);
	void render(SDL_Rect* camera, SDL_Rect* clip = NULL);
	
	//for debugging
	void renderAABB(SDL_Rect* camera);

	void setPos(b2Vec2 vec);
	void setPos(b2Vec2 vec, float angle);


	b2Body* body;

protected:
	Texture texture;
};


