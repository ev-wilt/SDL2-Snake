#pragma once
#include <vector>
#include "Sprite.h"

enum Direction { up, down, left, right };

class Snake
{
public:
	Snake(SDL_Renderer *renderer);
	void draw();
	void update();
	void checkInput(std::vector<SDL_Event> &events);
	bool ateFood();

private:
	std::vector<Sprite> snakeSegments;
	Direction currentDirection;
};

