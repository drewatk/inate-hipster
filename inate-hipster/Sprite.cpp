#include "headers/Sprite.h"


Sprite::Sprite() : texture(), posX(0), posY(0), velX(0), velY(0), forceX(0), forceY(0), colBox({ posX, posY, 0, 0 }), moveTimer(), angle(0), center(NULL), flip(SDL_FLIP_NONE), mass(1), angAcc(0), angVel(0)
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
	colBox.x = x;
	colBox.y = y;
}

void Sprite::free()
{
	texture.free();
}

void Sprite::render(SDL_Renderer* renderer, SDL_Rect& camera, SDL_Rect* clip)
{
	texture.render((int)posX - camera.x, (int)posY - camera.y, renderer, clip, angle, center, flip);
}

void Sprite::move(SDL_Rect& wall, SDL_Rect box)
{
	float timesincemove = moveTimer.getTicks() / 1000.f;

	//X calculations
	posX += velX * timesincemove;
	colBox.x = posX;
	velX += (forceX / mass) * timesincemove;

	if (posX < 0 || (posX + getWidth()) > wall.w)
	{ 
		velX *= -1; 
	}

	if (checkCol(getColBox(), box))
	{
		velX *= -1;
	}
	
	//Y calculations
	posY += velY * timesincemove;
	colBox.y = posY;
	velY += (forceY / mass) * timesincemove;

	if (posY < 0 || (posY + getHeight()) > wall.h)
	{
		velY *= -1;
	}

	if (checkCol(getColBox(), box))
	{
		velY *= -1;
	}


	//angular calculations
	angle += angVel * timesincemove;
	angVel += angAcc * timesincemove;
	
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

void Sprite::setMass(int usermass)
{
	mass = usermass;
}

bool Sprite::checkCol(SDL_Rect box1, SDL_Rect box2)
{
	if (box1.x < (box2.x + box2.w) &&
		(box1.x + box1.w) > box2.x &&
		box1.y < (box2.y + box2.h) &&
		(box1.h + box1.y) > box2.y)
		return true;
	else
		return false;
}