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
#include "Stack.h"

const int WINDOWWIDTH{ 1024 };
const int WINDOWHEIGHT{ 768 };

class Menu
{
public:
	const char* m_options[3];
	int m_optionSpawns[3];
	int m_x;
	int m_y;
	int m_w;
	int m_h;
	SDL_Color m_color;
};

const SDL_Color LTGREY = { 192,192,192,255 }; // light grey

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

	Array<Menu> g_menus(10);
	AStack<Menu*> g_stack(3);
	g_stack.Push(&(g_menus[0]));
	// main menu
	g_menus[0].m_options[0] = "1 - Sound";
	g_menus[0].m_optionSpawns[0] = 1;
	g_menus[0].m_options[1] = "2 - Graphics";
	g_menus[0].m_optionSpawns[1] = 2;
	g_menus[0].m_options[2] = "3 - Controls";
	g_menus[0].m_optionSpawns[2] = 3;
	g_menus[0].m_x = 16;
	g_menus[0].m_y = 16;
	g_menus[0].m_w = 768;
	g_menus[0].m_color = LTGREY;

	int x = g_stack.Top()->m_optionSpawns[0];
	if (x != 0)
	{
		g_stack.Push(&g_menus[x]);
	}

	if (g_stack.Top() != &g_menus[0])
	{
		g_stack.Pop();
	}

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