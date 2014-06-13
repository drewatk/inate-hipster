#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <sstream>
#include <stdio.h>
#include <string>

#include "headers/Sprite.h"
#include "headers/Texture.h"
#include "headers/Timer.h"

//Window and Surface Pointers
SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Renderer* renderer = NULL;

//Global font
TTF_Font* font = NULL;

//textures & sprites
Sprite playerSprite;
Texture words;

//Screen Constants
const int SCREEN_WIDTH = 1280, SCREEN_HEIGHT = 720;
const int SCREEN_FPS = 120;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;


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
		close();
		return 1;
	}
	
	//main loop flag
	bool quit = false;

	//event handler
	SDL_Event e;
	
	//set text color to black
	SDL_Color textColor = { 0, 0, 0, 255 };

	//FPS timer initialization
	Timer fpsTimer;
	std::stringstream timeText;
	int countedframes = 0;
	fpsTimer.start();

	//frame cap timer
	Timer capTimer;

	//start sprite in middle of screen
	playerSprite.setPos(0, (SCREEN_HEIGHT / 2) - (playerSprite.getHeight() / 2));
	playerSprite.startTimer();

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

		}
		//start the frame cap timer
		capTimer.start();

		//clalculate the fps, correct it if it's big
		float avgFPS = countedframes / (fpsTimer.getTicks() / 1000.f);
		if (avgFPS > 2000000)
			avgFPS = 0;
		
		//assemble the fps string
		timeText.str("");
		timeText << "Average FPS:" << avgFPS;
		
		//render text
		if (!words.loadFromRenderedText(timeText.str().c_str(), textColor, font, renderer))
			printf("Unable to render FPS texture!\n");
		words.render(20, 20, renderer);
		
		//handle sprite movement
		playerSprite.handleEvent(e);


		//Clear the screen
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);
				
		//move and Render the guy
		playerSprite.move();
		playerSprite.render(renderer);
			
		//render the words
		words.render(20, 20, renderer);
				
		SDL_RenderPresent(renderer);
		countedframes++;

		int frameTicks = capTimer.getTicks();
		if (frameTicks < SCREEN_TICKS_PER_FRAME)
		{
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
		}
	}

	close();

	return 0;
}

bool init()
{
	//initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Could not initialize SDL SDL Error:%s", SDL_GetError());
		return false;
	}

	//Create Window and 
	window = SDL_CreateWindow("inate-hipster", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Could not make window SDL Error:%s", SDL_GetError());
		return false;
	}

	//Create Renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED /*| SDL_RENDERER_PRESENTVSYNC*/);
	if (renderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	
	//Initialize SDL_img
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}

	//Initialize SDL_ttf, set font
	if (TTF_Init() == -1)
	{
		printf("Could not initialize SDL_ttf SDL_ttf error: %s\n", TTF_GetError()); 
		return false;
	}
	font = TTF_OpenFont("fonts/Sansus Webissimo-Regular.ttf", 20);
					
	
	return true;
}

bool loadMedia()
{
	bool success = true;

	playerSprite.load("sprites/man.png", renderer);
	
	return success;
}

void close()
{
	//playerTexture.free();
	words.free();

	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	//Destroy renderer
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}