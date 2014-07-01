#include "headers/Sprite.h"


Sprite::Sprite() : texture(), posX(0), posY(0), velX(0), velY(0), forceX(0), forceY(0), colBox({ posX, posY, 0, 0 }), moveTimer(), angle(0), center(NULL), flip(SDL_FLIP_NONE), mass(1)
{
}


Sprite::~Sprite()
{
	free();
}


bool Sprite::load(std::string filePath, SDL_Renderer* renderer)
{
	
	if (!texture.loadFromFile(filePath, renderer))
		return false;
	else
	{
		colBox.w = texture.getWidth();
		colBox.h = texture.getHeight();
	}

	return true;
}

void Sprite::setPos(int x, int y)
{
	posX = x;
	posY = y;
}

void Sprite::free()
{
	texture.free();
}

void Sprite::render(SDL_Renderer* renderer, SDL_Rect& camera, SDL_Rect* clip)
{
	texture.render((int)posX - camera.x, (int)posY - camera.y, renderer, clip, angle, center, flip);
}

void Sprite::move(SDL_Rect& wall)
{
	float timesincemove = moveTimer.getTicks() / 1000.f;

	if (posX < -1) { posX = 0; velX *= -1; }
	if (posX + getWidth() > wall.w + 1) { posX = wall.w - getWidth(); velX *= -1; }
	if (posY < -1) { posY = 0; velY *= -1; }
	if (posY + getHeight() > wall.h + 1) { posY = wall.h - getHeight(); velY *= -1; }

	posX += velX * timesincemove;
	posY += velY * timesincemove;
	velX += (forceX / mass) * timesincemove;
	velY += (forceY / mass) * timesincemove;
	
	moveTimer.start();

}

int Sprite::getWidth()
{
	return texture.getWidth();
}
int Sprite::getHeight()
{
	return texture.getHeight();
}

int Sprite::getX()
{
	return posX;
}

int Sprite::getY()
{
	return posY;
}

SDL_Rect Sprite::getColBox()
{
	return colBox;
}

void Sprite::setMass(int mass)
{
	mass = mass;
}