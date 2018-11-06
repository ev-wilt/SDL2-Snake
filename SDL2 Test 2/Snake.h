#pragma once
#include <vector>
#include "Sprite.h"
#include "Food.h"

enum Direction { up, down, left, right };

class Snake
{
public:
	Snake(SDL_Renderer *renderer);
	~Snake();
	void draw();
	void update();
	void checkInput(std::vector<SDL_Event> &events);
	bool ateFood(Food &food);

private:
	std::vector<Sprite> snakeSegments;
	Direction currentDirection;
	bool stopped;
};

