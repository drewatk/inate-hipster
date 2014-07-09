#include "screenConst.h"

SDL_Point worldToScreen(b2Vec2 vec)
{
	vec *= PIXELS_PER_METER;
	SDL_Point point;
	point.x = (int)vec.x;
	point.y = (int)vec.y;

	return point;
}

int worldToScreen(float n)
{
	return n * PIXELS_PER_METER;
}

float screenToWorld(int n)
{
	return n * METERS_PER_PIXEL;
}

double degToRad(double n)
{
	return (n * 3.14159265) / 180;
}

double radToDeg(double n)
{
	return (n / 3.14159265) * 180;
}