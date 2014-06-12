#pragma once

#include <SDL.h>
#include <string>

#include "Texture.h"

class Sprite
{
public:
	Sprite();
	~Sprite();
	bool load(std::string filePath, SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer);
	void move();
	void handleEvent(SDL_Event& e);
	void setPos(int x, int y);
	void free();
	int getWidth();
	int getHeight();

	const int SPRITE_MAX_ACCEL = 1;

private:
	Texture texture;
	SDL_Rect colBox;

	int posX, posY;
	int velX, velY;
};
