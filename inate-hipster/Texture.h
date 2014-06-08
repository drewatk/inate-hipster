#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Texture
{
public:
	//Initializes variables
	Texture();
	
	//Deallocates memory
	~Texture();

	//Loads image at specified path
	bool loadFromFile(std::string path, SDL_Renderer* renderer);

	//Deallocates texture
	void free();

	//Renders texture at given point
	void render(int x, int y, SDL_Renderer* renderer);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	SDL_Texture* m_Texture;

	//Image demensions
	int m_Width;
	int m_Height;

};

#endif