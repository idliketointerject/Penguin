#ifndef PENGUIN_H
#define PENGUIN_H
#include "Object.h"

class penguin: public object{
public:
	penguin();
	void move(bool keys[]);
	//ALLEGRO_BITMAP *bitmap;
    //float penguin_x;
	//float penguin_y;
	//int penguin_w;
	//int penguin_h;
	//int width;
	//int height;
};
#endif
