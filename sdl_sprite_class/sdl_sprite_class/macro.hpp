#pragma once
#include <SDL.h>
#include <time.h>

struct MACRO {
public:
	int mouse_x;
	int mouse_y;

	void init() {
		mouse_x            = 0;
		mouse_y            = 0;
	};
} macro;