#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

#include "Texture.h"

//Window and Surface Pointers
SDL_Window* g_window = NULL;
SDL_Surface* g_ScreenSurface = NULL;
SDL_Renderer* g_renderer = NULL;

//textures
Texture g_BananaTexture;
//Texture g_BackgroundTexture;


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
		printf("Couldn't load media\n");
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
				SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(g_renderer);

				//Render banana
				g_BananaTexture.render(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, g_renderer);

				SDL_RenderPresent(g_renderer);
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
		g_window = SDL_CreateWindow("VITAL TEAL WINDSHIELD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (g_window == NULL)
		{
			printf("Could not make g_window SDL Error:%s", SDL_GetError());
			success = false;
		}
		else
		{
			g_ScreenSurface = SDL_GetWindowSurface(g_window);
			g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
			if (g_renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
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

	success = g_BananaTexture.loadFromFile("sprites/bananaman.bmp", g_renderer);

	return success;
}

void close()
{
	g_BananaTexture.~Texture();

	//Destroy g_window
	SDL_DestroyWindow(g_window);
	g_window = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}
