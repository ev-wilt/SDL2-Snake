#pragma once
#include "Sprite.h"
class Food :
	public Sprite
{
public:
	Food(SDL_Renderer *renderer, const char *filename, int width, int height);
	~Food();
	void resetPosition();
};

