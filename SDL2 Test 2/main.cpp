#include "stdafx.h"
#include "Sprite.h"
#include <SDL\SDL.h>
#include <SDL\SDL_image.h>
#include <iostream>

int main(int argc, char *argv[]) {
	int posX = 100, posY = 100, width = 1280, height = 720;

	// Inital Setup
	SDL_Init(SDL_INIT_VIDEO);
	if (!IMG_Init(IMG_INIT_PNG)) {
		std::cerr << IMG_GetError() << std::endl;
	}
	SDL_Window *win = SDL_CreateWindow("SDL Snake", posX, posY, width, height, 0);

	// Present V-Sync caps the framerate to the monitor's V-Sync
	SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	Sprite test = Sprite(renderer, "lancer.png", 150, 200);

	// Game Loop
	while (true) {
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				break;
			}
		}

		SDL_RenderClear(renderer);
		/*
			Put drawing code here
		*/
		test.draw();
		test.setX(test.getX() + 3);
		SDL_RenderPresent(renderer);

	}

	// SDL Cleanup
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}