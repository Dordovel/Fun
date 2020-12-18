#ifndef RECTANGLE_HEADER
#define RECTANGLE_HEADER
#include<SDL2/SDL.h>

struct Rectangle
{
	SDL_Rect rect;
	SDL_Color color = {255,255,255,1};
	bool obstacle = false;
	int type;
	int localX, localY;
};

#endif //RECTANGLE_HEADER
