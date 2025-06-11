#define _CRT_SECURE_NO_WARNINGS
#include "Array.h"
#include "Bitvector.h"
#include "LinkedList.h"
#include "DLinkedList.h"

#include <SDL3/SDL.h>

#include <iostream>
#include <algorithm>
#include <ctime>

const int WINDOWWIDTH{ 1280 };
const int WINDOWHEIGHT{ 720 };

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		std::cerr << "Failed to init SDL: " << SDL_GetError() << "\n";
		return -1;
	}

	SDL_Window* window = SDL_CreateWindow(
		"DSA",
		WINDOWWIDTH,
		WINDOWHEIGHT,
		SDL_WINDOW_RESIZABLE
	);

	if (!window)
	{
		std::cout << "Window could not be created! SDL_ERROR: " << SDL_GetError() << "\n";
		SDL_Quit();
		return -1;
	}

	// Create renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
	// Enable vsync
	SDL_SetRenderVSync(renderer, 1);

	bool quit = false;
	SDL_Event event;

	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT)
			{
				quit = true;
			}
			if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE)
			{
				quit = true;
			}


		}

		// Render stuff
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 250); // Clear to black
		SDL_RenderClear(renderer);

		SDL_RenderPresent(renderer);

	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}