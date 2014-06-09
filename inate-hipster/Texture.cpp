#include "Texture.h"

Texture::Texture(): texture(NULL), width(0), height(0)
{
}

Texture::~Texture()
{
	//Deallocate
	free();
}

bool Texture::loadFromFile(std::string path, SDL_Renderer* renderer)
{
	
	//Gets rid of old texture
	free();

	//Final Texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		//SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0, 0));
		
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image demensions
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		//get rid of loadedSurface
		SDL_FreeSurface(loadedSurface);

	}

	texture = newTexture;
	return texture != NULL;
}

void Texture::free()
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;

	}
}

void Texture::render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip)
{
	SDL_Rect renderQuad = { x, y, width, height };

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	
	SDL_RenderCopy(renderer, texture, clip, &renderQuad);
}

int Texture::getWidth()
{
	return width;
}

int Texture::getHeight()
{
	return height;
}
