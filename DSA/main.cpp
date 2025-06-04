#define _CRT_SECURE_NO_WARNINGS
#include "Array.h"
#include "Bitvector.h"

#include <SDL3/SDL.h>

#include <iostream>
#include <algorithm>
#include <ctime>

const int WINDOWWIDTH{ 1280 };
const int WINDOWHEIGHT{ 720 };

const int MAPWIDTH = 16;
const int MAPHEIGHT = 16;
const int TILES = 12;
const int TILESIZE = 64;
const int LAYERS = 2;

/*
// 2D array for the map
Array2D<int> g_tilemap(MAPWIDTH, MAPHEIGHT);
*/

// 3D array for the map
Array3D<int> g_tilemap(MAPWIDTH, MAPHEIGHT, LAYERS);

// Array of tile textures 
SDL_Texture* g_tiles[TILES];

void DrawTilemap(SDL_Renderer* renderer, int p_x, int p_y)
{
	// Assuming you have const int LAYERS defined
	for (int z = 0; z < LAYERS; z++)
	{
		int bx = p_x;
		int by = p_y;

		for (int y = 0; y < MAPHEIGHT; y++)
		{
			for (int x = 0; x < MAPWIDTH; x++)
			{
				int tileIndex = g_tilemap.Get(x, y, z);

				
				if (tileIndex >= 0 && tileIndex < TILES)
				{
					SDL_FRect dst = {
						(float)bx,
						(float)by,
						(float)TILESIZE,
						(float)TILESIZE
					};
					SDL_RenderTexture(renderer, g_tiles[tileIndex], nullptr, &dst);
				}
				bx += TILESIZE;
			}
			bx = p_x;
			by += TILESIZE;
		}
	}
}



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

	SDL_Surface* temp;

	temp = SDL_LoadBMP("bmp/grass1.bmp");
	g_tiles[0] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_DestroySurface(temp);

	temp = SDL_LoadBMP("bmp/grass2.bmp");
	g_tiles[1] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_DestroySurface(temp);

	temp = SDL_LoadBMP("bmp/grass3.bmp");
	g_tiles[2] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_DestroySurface(temp);

	temp = SDL_LoadBMP("bmp/grass4.bmp");
	g_tiles[3] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_DestroySurface(temp);

	temp = SDL_LoadBMP("bmp/roadh.bmp");
	g_tiles[4] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_DestroySurface(temp);

	temp = SDL_LoadBMP("bmp/roadv.bmp");
	g_tiles[5] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_DestroySurface(temp);

	temp = SDL_LoadBMP("bmp/roadtopleft.bmp");
	g_tiles[6] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_DestroySurface(temp);

	temp = SDL_LoadBMP("bmp/roadtopright.bmp");
	g_tiles[7] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_DestroySurface(temp);

	temp = SDL_LoadBMP("bmp/roadbottomleft.bmp");
	g_tiles[8] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_DestroySurface(temp);

	temp = SDL_LoadBMP("bmp/roadbottomright.bmp");
	g_tiles[9] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_DestroySurface(temp);

	temp = SDL_LoadBMP("bmp/snow1.bmp");
	g_tiles[10] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_DestroySurface(temp);

	temp = SDL_LoadBMP("bmp/snow2.bmp");
	g_tiles[11] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_DestroySurface(temp);

	// "grass and snow"
	for (int y = 0; y < MAPHEIGHT; y++)
	{
		for (int x = 0; x < (MAPWIDTH / 2); x++)
		{
			g_tilemap.Get(x, y,0) = rand() % 4;
			g_tilemap.Get(x + (MAPWIDTH / 2), y,0) = (rand() % 2) + 10;
		}
	}

	// "Bridge"
	for (int x = 4; x < 10; x++)
	{
		g_tilemap.Get(x, 2,0) = 4;
		g_tilemap.Get(x, 6,0) = 4;
	}
	for (int y = 3; y < 7; y++)
	{
		g_tilemap.Get(4, y,0) = 5;
		g_tilemap.Get(9, y,0) = 5;
	}
	g_tilemap.Get(4, 2,0) = 6;
	g_tilemap.Get(9, 2,0) = 7;
	g_tilemap.Get(4, 6,0) = 8;
	g_tilemap.Get(9, 6,0) = 9;

	// Create another road
	for (int x = 0; x < (MAPWIDTH / 2); x++)
	{
		g_tilemap.Get(x, 8, 0) = 4;
	}
	// clear the second layer
	for (int y = 0; y < MAPHEIGHT; y++)
	{
		for (int x = 0; x < MAPWIDTH; x++)
		{
			g_tilemap.Get(x, y, 1) = -1;
		}
	}
	// add the transparent snow tiles over the grass.
	for (int y = 0; y < MAPHEIGHT; y++)
	{
		g_tilemap.Get((MAPWIDTH / 2) - 1, y, 1) = 12;
	}
	g_tilemap.Get((MAPWIDTH / 20) - 1, 2, 1) = -1;
	g_tilemap.Get((MAPWIDTH / 20) - 1, 6, 1) = -1;


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

		DrawTilemap(renderer, 0, 0);

		SDL_RenderPresent(renderer);

	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}