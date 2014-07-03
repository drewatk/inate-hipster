#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <string>

#include "Texture.h"
#include "Timer.h"

class Sprite
{
public:
	Sprite();
	~Sprite();
	bool load(std::string filePath, SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer, SDL_Rect& camera, SDL_Rect* clip = NULL);
	void Sprite::move(SDL_Rect& wall, SDL_Rect box);
	void setPos(int x, int y);
	void setMass(int usermass);
	void free();
	int getWidth();
	int getHeight();
	int getX();
	int getY();

	SDL_Rect getColBox();
	bool checkCol(SDL_Rect box1, SDL_Rect box2);

protected:
	Texture texture;
	SDL_Rect colBox;

	//translational variables
	int mass;
	float posX, posY;
	float velX, velY;
	float forceX, forceY;
	
	//rotation variables
	double angle;
	SDL_Point* center;
	SDL_RendererFlip flip;
	float angVel;
	float angAcc;
	

	Timer moveTimer;
};

#endif
