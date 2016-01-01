#pragma once
#include <SDL.h>
#include <string>

class sprite {
private:
	//SDL_Surface* surface;
	SDL_Texture* texture;
	int image_number;
	int xoffset;
	int yoffset;
	int width;
	int height;

	static SDL_Renderer* render_target;
public:
	// Sets the surface that all sprites will be rendered on
	static void set_render_target( SDL_Renderer* surface ) {
		render_target = surface;
	}


	// Loads a sprite from the external file specified
	bool load(std::string filename, int image_count, int xoffset, int yoffset) {
		SDL_Surface* loaded_image = NULL;
		//SDL_Surface* optimized_image = NULL;

		loaded_image = SDL_LoadBMP(filename.c_str());
		if (loaded_image != NULL) {
			texture = SDL_CreateTextureFromSurface(render_target, loaded_image);
			image_number = image_count;
			width = loaded_image->w;
			height = loaded_image->h;
			this->xoffset = xoffset;
			this->yoffset = yoffset;

			SDL_FreeSurface(loaded_image);

			return true;
		}
		else {
			return false;
		}
	}

	// Draws the sprite on the specified x and y coordinates
	void draw(int subimage, int x, int y) {
		SDL_Rect srcrect;
		srcrect.x = 0;
		srcrect.y = 0;
		srcrect.w = this->width;
		srcrect.h = this->height;
		SDL_Rect dstrect;
		dstrect.x = x - this->xoffset;
		dstrect.y = y - this->yoffset;
		dstrect.w = this->width;
		dstrect.h = this->height;

		SDL_RenderCopy( render_target , texture , &srcrect , &dstrect );
	};
	

	void draw_ext(int subimage, int x, int y, float xscale, float yscale, int rot, int colour, float alpha) {
		
	}

	// Clear the memory
	~sprite() {
		SDL_DestroyTexture(texture);
	}
};
SDL_Renderer* sprite::render_target;
