#include "stdafx.h"
#include "Sprite.h"
#include <iostream>

Sprite::Sprite(SDL_Renderer *renderer, const char *filename, int width, int height) :
	x(0),
	y(0),
	width(width),
	height(height),
	renderer(renderer),
	imageTexture(IMG_LoadTexture(renderer, filename))
{
	if (imageTexture == NULL) {
		std::cerr << "Failed to load IMG for sprite" << std::endl;
	}
}

void Sprite::draw() {
	SDL_QueryTexture(imageTexture, NULL, NULL, NULL, NULL);
	SDL_Rect textureRec = { this->x, this->y, this->width, this->height };
	SDL_RenderCopy(this->renderer, this->imageTexture, NULL, &textureRec);
}

void Sprite::setX(int x) {
	this->x = x;
}

void Sprite::setY(int y) {
	this->y = y;
}

int Sprite::getX() {
	return this->x;
}

int Sprite::getY() {
	return this->y;
}