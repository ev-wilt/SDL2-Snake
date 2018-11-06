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
	SDL_QueryTexture(this->imageTexture, NULL, NULL, NULL, NULL);
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

int Sprite::getWidth() {
	return this->width;
}

int Sprite::getHeight() {
	return this->height;
}

bool Sprite::isCollidingWith(Sprite sprite) {
	int left = this->x - (this->width / 2);
	int right = this->x + (this->width / 2);
	int top = this->y - (this->height / 2);
	int bottom = this->y + (this->height / 2);
	int spriteLeft = sprite.getX() - (sprite.getWidth() / 2);
	int spriteRight = sprite.getX() + (sprite.getWidth() / 2);
	int spriteTop = sprite.getY() - (sprite.getHeight() / 2);
	int spriteBottom = sprite.getY() + (sprite.getHeight() / 2);
	
	if ((bottom < spriteTop) || 
		(top > spriteBottom) ||
		(right < spriteLeft) ||
		(left > spriteRight)) {
		return false;
	}
	return true;
}

SDL_Texture *Sprite::getTexture() {
	return this->imageTexture;
}