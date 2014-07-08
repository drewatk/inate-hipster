#pragma once

#include <Box2D/Box2d.h>
#include <SDL.h>

const int SCREEN_WIDTH = 1920, SCREEN_HEIGHT = 1080;
const int PIXELS_PER_METER = 20;
const float METERS_PER_PIXEL = 1.0f / (float)PIXELS_PER_METER;

SDL_Point worldToScreen(b2Vec2 vec);
int worldToScreen(float n);

float screenToWorld(int n);
