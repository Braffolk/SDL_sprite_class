#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <SDL.h>
#include <time.h>
#include <vector>

#include "macro.hpp"
#include "sprite.hpp"

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
int current_time         = 0;
int mouse_x              = 0;
int mouse_y              = 0;

int main(int argc, char* args[])
{
	// The window we'll be rendering to
	SDL_Window* window = NULL;
	SDL_Renderer* screen_renderer = NULL;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		// Create window
		window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			screen_renderer = SDL_CreateRenderer( window , -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (screen_renderer == NULL) {
				SDL_DestroyWindow( window );
				SDL_Quit();
			}
		}
	}

	// Macros
	macro.init();

	sprite::set_render_target( screen_renderer );

	sprite* spr_test = new sprite();
	spr_test->load( "test.bmp" , 1 , 16 , 16 );

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
		current_time = ((clock() - time_start) / CLOCKS_PER_SEC) * 1000;
		if (current_time >= last_frame + frames_till_update) {
			SDL_GetMouseState(&macro.mouse_x, &macro.mouse_y);

			// Clear renderer
			SDL_RenderClear(screen_renderer);


			spr_test->draw( 0 , macro.mouse_x , macro.mouse_y );


			// Draw renderer
			SDL_RenderPresent(screen_renderer);

			// Update time variables
			last_frame = current_time;
		}
	}

	// Destroy window
	SDL_DestroyWindow(window);

	// Quit SDL subsystems
	SDL_Quit();

	return 0;
}