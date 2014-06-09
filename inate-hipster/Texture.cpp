#include "Texture.h"

Texture::Texture(): m_Texture(NULL), m_Width(0), m_Height(0)
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
			m_Width = loadedSurface->w;
			m_Height = loadedSurface->h;
		}

		//get rid of loadedSurface
		SDL_FreeSurface(loadedSurface);

	}

	m_Texture = newTexture;
	return m_Texture != NULL;
}

void Texture::free()
{
	if (m_Texture != NULL)
	{
		SDL_DestroyTexture(m_Texture);
		m_Texture = NULL;
		m_Width = 0;
		m_Height = 0;

	}
}

void Texture::render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip)
{
	SDL_Rect renderQuad = { x, y, m_Width, m_Height };

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	
	SDL_RenderCopy(renderer, m_Texture, clip, &renderQuad);
}

int Texture::getWidth()
{
	return m_Width;
}

int Texture::getHeight()
{
	return m_Height;
}
