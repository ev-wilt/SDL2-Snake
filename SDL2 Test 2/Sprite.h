#pragma once
#include <SDL\SDL_image.h>

class Sprite
{
public:
	Sprite(SDL_Renderer *renderer, const char *filename, int width, int height);
	void draw();
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	void changeXBy(int dx);
	void changeYBy(int dy);
	int getWidth();
	int getHeight();
	bool isCollidingWith(Sprite sprite);
	SDL_Texture *getTexture();

private:
	SDL_Texture *imageTexture;
	SDL_Renderer *renderer;
	int width;
	int height;
	int x;
	int y;
};