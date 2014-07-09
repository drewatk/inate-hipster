#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

#include "worldConst.h"

class Texture
{
public:
	//Initializes variables
	Texture();
	
	//Deallocates memory
	~Texture();

	//Loads image at specified path
	bool loadFromFile(std::string path);

	//Deallocates texture
	void free();

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void render(SDL_Point point, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Gets image dimensions
	int getWidth();
	int getHeight();

	#ifdef _SDL_TTF_H
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* font);
	#endif

private:
	SDL_Texture* texture;

	//Image demensions
	int width;
	int height;

};