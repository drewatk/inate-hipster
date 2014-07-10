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
	void renderHitbox(SDL_Rect* camera);

protected:
	b2Body* body;
	Texture texture;
};


