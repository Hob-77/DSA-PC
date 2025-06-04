#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <SDL3/SDL.h>
#include "Array.h"
#include "Bitvector.h"
#include "Linked Lists.h"

const int WINDOWWIDTH{ 1024 };
const int WINDOWHEIGHT{ 768 };

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
	SDL_Renderer* renderer = SDL_CreateRenderer(window,NULL);

	// Enable vsync
	SDL_SetRenderVSync(renderer, 1);


	// Creating Linked list
	SListNode<int>* list = new SListNode<int>;
	list->m_data = 10;
	// insert 30 and then 20 before that, so the list is 10,20,30.
	list->InsertAfter(30);
	list->InsertAfter(20);
	std::cout << "the list contains: ";
	// create a new iterator and make it point to the beginning of the list.
	SListNode<int>* itr = list;
	std::cout << itr->m_data << ", ";
	// move the iterator to the next node in the list.
	itr = itr->m_next;
	std::cout << itr->m_data << ", ";
	// move the iterator forward again.
	itr = itr->m_next;
	std::cout << itr->m_data << ". ";
	// reset the iterator to the beginning again.
	itr = list;


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

			// Exit with escape key
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