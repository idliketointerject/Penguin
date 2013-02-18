#ifndef PENGUIN_H
#define PENGUIN_H
#include "initgame.h"

class penguin{
public:
	penguin();
	ALLEGRO_BITMAP *bitmap;
    float penguin_x;
	float penguin_y;
	int penguin_w;
	int penguin_h;
	int width;
	int height;
};
#endif
