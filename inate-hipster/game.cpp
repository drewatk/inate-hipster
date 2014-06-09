#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

#include "Texture.h"

//Window and Surface Pointers
SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Renderer* renderer = NULL;

//textures
Texture bananaTexture;
Texture backgroundTexture;


//Screen Dementions
const int SCREEN_WIDTH = 1280, SCREEN_HEIGHT = 720;

//Prototypes
bool init();
bool loadMedia();
void close();

int main(int argc, char* argv[])
{
	//Initializes SDL
	if (!init())
	{
		return 1;
	}
	//Loads surfaces
	if (!loadMedia())
	{
		printf("Couldn't load media SDL Error:%s\n", SDL_GetError());
	}
	else
	{
		//main loop
		bool quit = false;

		SDL_Event e;
		

		while (!quit)
		{
			while (SDL_PollEvent(&e) != 0) 
			{
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}

				//Clear the screen
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(renderer);

				backgroundTexture.render(0, 0, renderer);
				
				//Render banana
				bananaTexture.render((SCREEN_WIDTH / 2) - (bananaTexture.getWidth() / 2), (SCREEN_HEIGHT / 2) - (bananaTexture.getHeight() / 2), renderer);
				

				SDL_RenderPresent(renderer);
			}
		}
	}

	close();

	return 0;
}

bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Could not initialize SDL SDL Error:%s", SDL_GetError());
		success = false;
	}
	else
	{
		window = SDL_CreateWindow("VITAL TEAL WINDSHIELD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Could not make window SDL Error:%s", SDL_GetError());
			success = false;
		}
		else
		{
			screenSurface = SDL_GetWindowSurface(window);
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}

		}
	}
	
	return success;
}

bool loadMedia()
{
	bool success = true;

	success = bananaTexture.loadFromFile("sprites/bananaman.bmp", renderer);

	success = backgroundTexture.loadFromFile("sprites/tiles.jpg", renderer);

	return success;
}

void close()
{
	bananaTexture.~Texture();

	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}
