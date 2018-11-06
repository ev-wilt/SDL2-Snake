#include "stdafx.h"
#include "Snake.h"
#include <iostream>

Snake::Snake(SDL_Renderer *renderer) :
	snakeSegments(std::vector<Sprite> (5, Sprite(renderer, "lancer.png", 50, 50))),
	currentDirection(Direction::right)
{
	// Set segment coordinates to their proper position
	for (int i = 0; i < this->snakeSegments.size(); ++i) {
		snakeSegments[i].setX(200 - (i * 50));
		snakeSegments[i].setY(500);
	}
}

void Snake::draw() {
	for (int i = 0; i < this->snakeSegments.size(); ++i) {
		snakeSegments[i].draw();
	}
}

void Snake::update() {
	
	// Set new position
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

	// Check collisions

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

bool Snake::ateFood() {
	return false;
}