#include "stdafx.h"
#include "Food.h"
#include <cstdlib>
#include <ctime>


Food::Food(SDL_Renderer *renderer, const char *filename, int width, int height):
	Sprite(renderer, filename, width, height)
{
	srand(time(NULL));
	this->setY((std::rand() * 50) % (800 - 50));
	this->setX((std::rand() * 50) % (1200 - 50));
}


Food::~Food()
{
	SDL_DestroyTexture(this->getTexture());
}

void Food::resetPosition() {
	this->setY((std::rand() * 50) % (800 - 50));
	this->setX((std::rand() * 50) % (1200 - 50));
}