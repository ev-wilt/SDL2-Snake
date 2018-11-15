#include "stdafx.h"
#include "Snake.h"
#include <iostream>


// Overloaded constructor
Snake::Snake(SDL_Renderer *renderer) :
	snakeSegments(std::vector<Sprite>(3, Sprite(renderer, "assets/snake_segment.png", 50, 50))),
	currentDirection(Direction::right),
	stopped(true),
	hasChangedDirection(false) 
{
	snakeSegments[0] = Sprite(renderer, "assets/snake_head.png", 50, 50);

	// Set segment coordinates to their proper position
	for (int i = 0; i < this->snakeSegments.size(); ++i) {
		snakeSegments[i].setX(200 - (i * 50));
		snakeSegments[i].setY(500);
	}
}

// Destructor
Snake::~Snake() {
	for (int i = 0; i < this->snakeSegments.size(); ++i) {
		SDL_DestroyTexture(this->snakeSegments[i].getTexture());
	}
}

// Draws each segment of the snake
void Snake::draw() {
	for (int i = this->snakeSegments.size() - 1; i >= 0; --i) {
		snakeSegments[i].draw();
	}
}

// Updates the snake's position and checks for collisions
void Snake::update() {

	// Check if next move will cause snake to collide with wall
	Sprite head = this->snakeSegments[0];
	if ((this->currentDirection == Direction::up && head.getY() == 0) ||
		(this->currentDirection == Direction::down && head.getY() == (800 - 50)) ||
		(this->currentDirection == Direction::left && head.getX() == 0) ||
		(this->currentDirection == Direction::right && head.getX() == (1200 - 50))) {
		this->stopped = true;
	}
	
	// Set new position
	if (!this->stopped) {
		for (int i = this->snakeSegments.size() - 1; i >= 1; --i) {
			snakeSegments[i].setX(snakeSegments[i - 1].getX());
			snakeSegments[i].setY(snakeSegments[i - 1].getY());
		}
		if (this->currentDirection == Direction::up) {
			snakeSegments[0].changeYBy(-50);
		}
		else if (this->currentDirection == Direction::down) {
			snakeSegments[0].changeYBy(50);
		}
		else if (this->currentDirection == Direction::left) {
			snakeSegments[0].changeXBy(-50);
		}
		else if (this->currentDirection == Direction::right) {
			snakeSegments[0].changeXBy(50);
		}
	}

	// Check if snake has hit itself
	for (int i = 1; i < this->snakeSegments.size(); ++i) {
		if (this->snakeSegments[0].getX() == this->snakeSegments[i].getX() &&
			this->snakeSegments[0].getY() == this->snakeSegments[i].getY()) {
			this->stopped = true;
		}
	}

}

// Checks the input queue and responds to the appropriate events
void Snake::checkInput(std::vector<SDL_Event> &events, unsigned short updateCounter) {
	if (!this->hasChangedDirection) {
		Direction previous = this->currentDirection;
		for (int i = 0; i < events.size(); ++i) {
			if (events[i].type == SDL_KEYDOWN) {
				switch (events[i].key.keysym.scancode) {
				case SDL_SCANCODE_UP:
					if (this->currentDirection != Direction::down && !this->stopped) {
						this->currentDirection = Direction::up;
						this->snakeSegments[0].setAngle(270);
					}
					break;
				case SDL_SCANCODE_DOWN:
					if (this->currentDirection != Direction::up && !this->stopped) {
						this->currentDirection = Direction::down;
						this->snakeSegments[0].setAngle(90);
					}
					break;
				case SDL_SCANCODE_LEFT:
					if (this->currentDirection != Direction::right && !this->stopped) {
						this->currentDirection = Direction::left;
						this->snakeSegments[0].setAngle(180);
					}
					break;
				case SDL_SCANCODE_RIGHT:
					if (this->currentDirection != Direction::left && !this->stopped) {
						this->currentDirection = Direction::right;
						this->snakeSegments[0].setAngle(0);
					}
					break;
				case SDL_SCANCODE_RETURN:	// Pause/unpause game on enter press
					this->stopped = !this->stopped;
					break;
				}
				break;
			}
		}

		// Only change direction once per movement of the snake
		if (this->currentDirection != previous) {
			this->hasChangedDirection = true;
		}
	}

	if (updateCounter == 20) {
		this->hasChangedDirection = false;
	}
}

// Checks if the snake is in the same location as the food
bool Snake::ateFood(Food &food) {
	if (this->snakeSegments[0].getX() == food.getX() &&
		this->snakeSegments[0].getY() == food.getY()) {
		return true;
	}
	return false;
}

// Appends a new segment onto the snake
void Snake::increaseSize(SDL_Renderer *renderer) {
	Sprite newSegment = Sprite(renderer, "assets/snake_segment.png", 50, 50);
	Sprite tail = this->snakeSegments[this->snakeSegments.size() - 1];
	newSegment.setX(tail.getX());
	newSegment.setY(tail.getY());
	this->snakeSegments.push_back(newSegment);
}

// Checks each segment for a collision
bool Snake::isCollidingWith(Sprite &sprite) {
	for (int i = 0; i < this->snakeSegments.size(); ++i) {
		if (this->snakeSegments[i].isCollidingWith(sprite)) {
			return true;
		}
	}
	return false;
}
