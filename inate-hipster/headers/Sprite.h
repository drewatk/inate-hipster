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
	void render(SDL_Renderer* renderer);
	void move(SDL_Rect& wall);
	void handleEvent(SDL_Event& e);
	void setPos(int x, int y);
	void free();
	int getWidth();
	int getHeight();
	int getX();
	int getY();
	void startTimer();


private:
	Texture texture;
	SDL_Rect colBox;

	int posX, posY;
	int velX, velY;

	Timer moveTimer;

	const int SPRITE_MAX_ACCEL = 10;
};

#endif
