#include "headers/Sprite.h"


Sprite::Sprite() : texture(), posX(0), posY(0), velX(0), velY(0), colBox({posX, posY,0,0})
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

void Sprite::render(SDL_Renderer* renderer)
{
	texture.render(posX, posY, renderer);
}

void Sprite::move()
{
	posX += velX;
	posY += velY;
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