#include "stdafx.h"
#include "Sprite.h"
#include "Snake.h"
#include "Food.h"
#include <SDL\SDL.h>
#include <SDL\SDL_image.h>
#include <iostream>
#include <vector>

// Event Queue
std::vector<SDL_Event> &getEvents()
{
	static std::vector<SDL_Event> events;
	return events;
}

int main(int argc, char *argv[]) {
	int posX = 100, posY = 100, width = 1200, height = 800;

	// Inital Setup
	SDL_Init(SDL_INIT_VIDEO);
	if (!IMG_Init(IMG_INIT_PNG)) {
		std::cerr << IMG_GetError() << std::endl;
	}
	SDL_Window *win = SDL_CreateWindow("SDL Snake", posX, posY, width, height, 0);

	// Present V-Sync caps the framerate to the monitor's V-Sync
	SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	Snake player = Snake(renderer);
	Food food = Food(renderer, "assets/food.png", 50, 50);
	Sprite background = Sprite(renderer, "assets/background.png", 1200, 800);

	// Game Loop
	bool running = true;
	unsigned short updateCounter = 0;
	while (running) {

		// Save user input to a queue
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0) {
			getEvents().push_back(e);
		}

		for (int i = 0; i < getEvents().size(); ++i) {
			if (getEvents()[i].type == SDL_QUIT) {
				running = false;
			}
		}

		// Do sprite updates every 20 frames
		player.checkInput(getEvents(), updateCounter);
		if (updateCounter == 20) {
			player.update();
			if (player.ateFood(food)) {
				while (player.isCollidingWith(food)) {
					food.resetPosition();
				}
				player.increaseSize(renderer);
			}
			updateCounter = 0;
		}

		// Draw to renderer
		SDL_RenderClear(renderer);
		background.draw();
		food.draw();
		player.draw();
		SDL_RenderPresent(renderer);

		getEvents().clear();
		updateCounter++;
	}

	// SDL Cleanup
	SDL_DestroyTexture(background.getTexture());
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}