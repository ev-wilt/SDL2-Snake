#include "stdafx.h"
#include "Food.h"
#include <cstdlib>
#include <ctime>

// Overloaded constructor
Food::Food(SDL_Renderer *renderer, const char *filename, int width, int height):
	Sprite(renderer, filename, width, height)
{
	srand(time(NULL));
	this->resetPosition();
}

// Destructor
Food::~Food() {
	SDL_DestroyTexture(this->getTexture());
}

// Updates the food to a new random position
void Food::resetPosition() {
	this->setY((std::rand() * 50) % (800 - 50));
	this->setX((std::rand() * 50) % (1200 - 50));
}