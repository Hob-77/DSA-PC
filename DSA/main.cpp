#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

#include <SDL3/SDL.h>
#include <glad/glad.h>

#include "Array.h"
#include "Bitvector.h"
#include "LinkedLists.h"
#include "DLinkedLists.h"
#include "Stack.h"
#include "Queue.h"
#include "HashTable.h"

const int WINDOWWIDTH{ 1920 };
const int WINDOWHEIGHT{ 1080 };

int main(int argc, char* argv[])
{
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		std::cerr << "Failed to init SDL: " << SDL_GetError() << "\n";
		return -1;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	SDL_Window* window = SDL_CreateWindow(
		"DSA, SDL3 and OpenGL 4.6",
		WINDOWWIDTH,
		WINDOWHEIGHT,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
	);

	if (!window)
	{
		std::cout << "Window could not be created! SDL_ERROR: " << SDL_GetError() << "\n";
		SDL_Quit();
		return -1;
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	if (!glContext) 
	{
		std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << "\n";
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) 
	{
		std::cerr << "Failed to initialize GLAD\n";
		SDL_GL_DestroyContext(glContext);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	printf("OpenLGL Version: %s\n", glGetString(GL_VERSION));
	printf("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	// Enable V-Sync
	SDL_GL_SetSwapInterval(1);

	glViewport(0, 0, WINDOWWIDTH, WINDOWHEIGHT);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

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

			if (event.type == SDL_EVENT_WINDOW_RESIZED)
			{
				int newWidth = event.window.data1;
				int newHeight = event.window.data2;
				glViewport(0, 0, newWidth, newHeight);
			}
		}

		// Render
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		SDL_GL_SwapWindow(window);
	}

	SDL_GL_DestroyContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}