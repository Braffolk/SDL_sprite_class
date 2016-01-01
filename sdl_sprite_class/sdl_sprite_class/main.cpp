#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <SDL.h>
#include <time.h>
#include <vector>

#include "macro.hpp"
using namespace std;


SDL_Surface* screen_surface = NULL;



bool game_running = true;
// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// FPS & TIME CONTROL
int FPS                  = 60;
int last_frame           = time(0) * 1000;
float frames_till_update = 1000 / FPS;
double time_start        = clock();
int current_time         = ((clock() - time_start) / CLOCKS_PER_SEC) * 1000;
int mouse_x              = 0;
int mouse_y              = 0;

int main(int argc, char* args[])
{
	// The window we'll be rendering to
	SDL_Window* window = NULL;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		// Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			// Get window surface
			screen_surface = SDL_GetWindowSurface(window);

			// Fill the surface white
			SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, rand() * 255, rand() * 255, rand() * 255));

			// Update the surface
			SDL_UpdateWindowSurface(window);
		}
	}

	// Macros
	macro.init();

	// Main Loop
	SDL_Event event;
	while (game_running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				game_running = false;
				break;
			}
		}


		// FPS Clamped 
		if (current_time >= last_frame + frames_till_update) {


			// Update draw area
			SDL_UpdateWindowSurface(window);
			// Update time variables
			current_time = ((clock() - time_start) / CLOCKS_PER_SEC) * 1000;
			last_frame = current_time;
		}
	}

	// Destroy window
	SDL_DestroyWindow(window);

	// Quit SDL subsystems
	SDL_Quit();

	return 0;
}