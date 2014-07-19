#pragma once

#include <Box2D\Box2D.h>
#include <SDL.h>
#include "ContactListener.h"

//Level constants
const int LEVEL_WIDTH = 3622;
const int LEVEL_HEIGHT = 3877;

//Window and Surface Pointers
extern SDL_Window* window;
extern SDL_Surface* screenSurface;
extern SDL_Renderer* renderer;

//Box2D object constants
extern b2World* worldptr;
extern ContactListener ContactListenerInstance;