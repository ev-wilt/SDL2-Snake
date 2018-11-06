#include "stdafx.h"
#include "Sprite.h"
#include "Snake.h"
#include <SDL\SDL.h>
#include <SDL\SDL_image.h>
#include <iostream>
#include <vector>

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

	// Game Loop
	bool running = true;
	unsigned short updateCounter = 0;
	while (running) {
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0) {
			getEvents().push_back(e);
		}

		for (int i = 0; i < getEvents().size(); ++i) {
			if (getEvents()[i].type == SDL_QUIT) {
				running = false;
			}
		}

		player.checkInput(getEvents());
		SDL_RenderClear(renderer);
		/*
			Put drawing code here
		*/
		if (updateCounter == 50) {
			player.update();
			updateCounter = 0;
		}
		player.draw();
		SDL_RenderPresent(renderer);
		getEvents().clear();
		updateCounter++;
	}

	// SDL Cleanup
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}