#include "penguin.h"

penguin::penguin(){
	bitmap = al_load_bitmap("resources/images/penguin.png");
	penguin_w = al_get_bitmap_width(bitmap);
	penguin_h = al_get_bitmap_height(bitmap);
	penguin_x = SCREEN_W / 20.0;
	penguin_y = SCREEN_H / 2.0 - penguin_h / 2.0;
}