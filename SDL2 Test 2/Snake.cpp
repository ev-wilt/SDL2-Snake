#include "stdafx.h"
#include "Snake.h"
#include <iostream>

Snake::Snake(SDL_Renderer *renderer) :
	snakeSegments(std::vector<Sprite>(3, Sprite(renderer, "snake_segment.png", 50, 50))),
	currentDirection(Direction::right),
	stopped(false)
{
	// Set segment coordinates to their proper position
	for (int i = 0; i < this->snakeSegments.size(); ++i) {
		snakeSegments[i].setX(200 - (i * 50));
		snakeSegments[i].setY(500);
	}
}

Snake::~Snake() {
	for (int i = 0; i < this->snakeSegments.size(); ++i) {
		SDL_DestroyTexture(this->snakeSegments[i].getTexture());
	}
}

void Snake::draw() {
	for (int i = 0; i < this->snakeSegments.size(); ++i) {
		snakeSegments[i].draw();
	}
}

void Snake::update() {

	// Check if next move will cause snake to collide with wall
	Sprite head = this->snakeSegments[0];
	if (this->currentDirection == Direction::up && head.getY() == 0) {
		this->stopped = true;
	}
	else if (this->currentDirection == Direction::down && head.getY() == (800 - 50)) {
		this->stopped = true;
	}
	else if (this->currentDirection == Direction::left && head.getX() == 0) {
		this->stopped = true;
	}
	else if (this->currentDirection == Direction::right && head.getX() == (1200 - 50)) {
		this->stopped = true;
	}
	
	// Set new position
	if (!this->stopped) {
		for (int i = this->snakeSegments.size() - 1; i >= 1; --i) {
			snakeSegments[i].setX(snakeSegments[i - 1].getX());
			snakeSegments[i].setY(snakeSegments[i - 1].getY());
		}
		if (this->currentDirection == Direction::up) {
			snakeSegments[0].setY(snakeSegments[0].getY() - 50);
		}
		else if (this->currentDirection == Direction::down) {
			snakeSegments[0].setY(snakeSegments[0].getY() + 50);
		}
		else if (this->currentDirection == Direction::left) {
			snakeSegments[0].setX(snakeSegments[0].getX() - 50);
		}
		else if (this->currentDirection == Direction::right) {
			snakeSegments[0].setX(snakeSegments[0].getX() + 50);
		}
	}

}

void Snake::checkInput(std::vector<SDL_Event> &events) {
	for (int i = 0; i < events.size(); ++i) {
		if (events[i].type == SDL_KEYDOWN) {
			switch (events[i].key.keysym.scancode) {
				case SDL_SCANCODE_UP:
					this->currentDirection = Direction::up;
					break;
				case SDL_SCANCODE_DOWN:
					this->currentDirection = Direction::down;
					break;
				case SDL_SCANCODE_LEFT:
					this->currentDirection = Direction::left;
					break;
				case SDL_SCANCODE_RIGHT:
					this->currentDirection = Direction::right;
					break;
			}
		}
	}
}

bool Snake::ateFood(Food &food) {
	if (this->snakeSegments[0].isCollidingWith(food)) {
		return true;
	}
	return false;
}