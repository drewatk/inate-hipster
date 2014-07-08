#include <Box2D/Box2D.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <sstream>
#include <stdio.h>
#include <string>

#include "Entity.h"
#include "screenConst.h"
#include "Texture.h"
#include "Timer.h"
#include "worldConst.h"

//Global font
TTF_Font* font = NULL;

//textures
Texture FPSwords;
Texture backgroundTexture;

//Screen Constants
const int SCREEN_FPS = 1000000;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

//Box2d time constants
const float32 timeStep = 1.0f / 60.0f;
const int32 velocityIterations = 6;
const int32 positionIterations = 2;

//Prototypes
bool init();
bool loadMedia();
void close();
void cameraMove(SDL_Rect& camera, b2Body* ship, Texture texture);

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
	
	//camera rectangle
	SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	//set text color to black
	SDL_Color textColor = { 0xff, 0xff, 0xff, 0xff };

	//FPS timer initialization
	Timer fpsTimer;
	std::stringstream timeText;
	int countedFrames = 0;
	int fpsShown = 0;
	fpsTimer.start();

	//frame cap timer
	Timer capTimer;

	//accumulator for physics steps
	double accumulator = 0.0;
	Timer accTimer;

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

		//clalculate the fps
		if (fpsTimer.getTicks() > 1000)
		{
			fpsShown = countedFrames;
			fpsTimer.start();
			countedFrames = 0;
		}
		
		//Accumulator 
		accumulator += (accTimer.getTicks())/1000.f;
		accTimer.start();

		while (accumulator >= timeStep)
		{
			worldptr->Step(timeStep, velocityIterations, positionIterations);
			accumulator -= timeStep;

		}

		FPSwords.render(20, 20);
		//assemble the fps string
		timeText.str("");
		timeText << "FPS:" << fpsShown;
		
		//render text
		if (!FPSwords.loadFromRenderedText(timeText.str().c_str(), textColor, font))
			printf("Unable to load the FPS texture!\n");

		//handle sprite and camera movement
		//cameraMove(camera, ship, shipTexture);

		//Clear the screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		//render the words and background
		backgroundTexture.render(0, 0, &camera);
		FPSwords.render(20, 20);

		//render
		SDL_RenderPresent(renderer);
		countedFrames++;

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
	window = SDL_CreateWindow("inate-hipster", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
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
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	
	//Initialize SDL_img
	int imgFlags = IMG_INIT_PNG | IMG_INIT_TIF;
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
	
	//Create B2D world
	b2Vec2 gravity(0.0f, 1.0f);
	worldptr = new b2World(gravity);
	
	return true;
}

bool loadMedia()
{
	bool success = true;
	
	backgroundTexture.loadFromFile("sprites/background.tif");
	
	return success;
}

void close()
{
	//playerTexture.free();
	FPSwords.free();

	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	//Destroy renderer
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();

	//Delete Box2d world
	delete worldptr;
}

void cameraMove(SDL_Rect& camera, b2Body* ship, Texture texture)
{
	//Center the camera over the ship
	camera.x = (ship->GetPosition().x + texture.getWidth() / 2) - SCREEN_WIDTH / 2;
	camera.y = (ship->GetPosition().y + texture.getHeight() / 2) - SCREEN_HEIGHT / 2;

	//Keep the camera in bounds
	if (camera.x < 0)
	{
		camera.x = 0;
	}
	if (camera.y < 0)
	{
		camera.y = 0;
	}
	if (camera.x > LEVEL_WIDTH - camera.w)
	{
		camera.x = LEVEL_WIDTH - camera.w;
	}
	if (camera.y > LEVEL_HEIGHT - camera.h)
	{
		camera.y = LEVEL_HEIGHT - camera.h;
	}
}