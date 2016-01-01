#pragma once
#include <SDL.h>
#include <string>

class sprite {
private:
	SDL_Surface* surface;
	int image_number;
	int xoffset;
	int yoffset;
	int width;
	int height;

	static SDL_Surface* render_target;
public:
	// Sets the surface that all sprites will be rendered on
	static void set_render_target( SDL_Surface* surface ) {
		render_target = surface;
	}

	// Loads a sprite from the external file specified
	bool load(std::string filename, int image_count, int xoffset, int yoffset) {
		SDL_Surface* loaded_image = NULL;
		SDL_Surface* optimized_image = NULL;

		loaded_image = SDL_LoadBMP(filename.c_str());
		if (loaded_image != NULL) {
			optimized_image = SDL_ConvertSurfaceFormat(loaded_image, SDL_PIXELFORMAT_RGBA8888, 0);
			SDL_FreeSurface(loaded_image);

			surface = optimized_image;
			image_number = image_count;
			width = optimized_image->w;
			height = optimized_image->h;
			this->xoffset = xoffset;
			this->yoffset = yoffset;

			return true;
		}
		else {
			return false;
		}
	}

	// Draws the sprite on the specified x and y coordinates
	void draw(int subimage, int x, int y) {
		SDL_Rect dstrect;
		dstrect.x = x - this->xoffset;
		dstrect.y = y - this->yoffset;
		dstrect.w = this->width;
		dstrect.h = this->height;
		SDL_BlitSurface( this->surface , NULL , render_target, &dstrect );
	}

	// Clear the memory
	~sprite() {
		SDL_FreeSurface(surface);
	}
};
SDL_Surface* sprite::render_target;
