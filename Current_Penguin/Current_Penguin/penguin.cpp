#include "penguin.h"

penguin::penguin(){

	//bitmap = al_load_bitmap("resources/images/penguin.png");
	//penguin_w = al_get_bitmap_width(bitmap);
	//penguin_h = al_get_bitmap_height(bitmap);
	//penguin_x = SCREEN_W / 20.0;
	//penguin_y = SCREEN_H / 2.0 - penguin_h / 2.0;
}

void penguin::move(bool keys[]){
		// Vertical Movement
		if (keys[KEY_UP] && keys[KEY_DOWN])
			dirY = 0;
		else if(keys[KEY_UP])
			if(getY() == 0)
				dirY=0;
			else
				dirY = -1;
		else if(keys[KEY_DOWN])//need to define BoundY and BoundX as 'getbitmapwidth/height'
			if(getY() ==HEIGHT - getBoundY())
				dirY = 0;
			else
				dirY = 1;
		else dirY  = 0;
		// Horizontal movement
		if (keys[KEY_LEFT] && keys[KEY_RIGHT])//need to define boundx 
			dirX = 0;
		else if (keys[KEY_LEFT])
			if(getX() == 0)
				dirX = 0;
			else
				dirX = -1;
		else if (keys[KEY_RIGHT])
			if(getX() == WIDTH - getBoundX())
				dirX = 0;
			else
				dirX = 1;
		else dirX = 0;
	this->update();
}