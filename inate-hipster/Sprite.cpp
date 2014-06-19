#include "headers/Sprite.h"


Sprite::Sprite() : texture(), posX(0), posY(0), velX(0), velY(0), colBox({ posX, posY, 0, 0 }), moveTimer()
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

void Sprite::render(SDL_Renderer* renderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	texture.render((int)posX, (int)posY, renderer, clip, angle, center, flip);
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
	moveTimer.start();

}

void Sprite::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			velY -= SPRITE_MAX_ACCEL;
			break;
		case SDLK_DOWN:
			velY += SPRITE_MAX_ACCEL;
			break;
		case SDLK_LEFT:
			velX -= SPRITE_MAX_ACCEL;
			break;
		case SDLK_RIGHT:
			velX += SPRITE_MAX_ACCEL;
			break;
		default:
			break;
		}
	}
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