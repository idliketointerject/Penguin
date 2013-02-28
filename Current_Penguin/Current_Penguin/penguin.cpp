#include "penguin.h"

penguin::penguin() : object() 
{
	setCollidable(true);
	setLives(3);
}

penguin::penguin(char *bitmapPath) : object(bitmapPath)
{
	setCollidable(true);
	setLives(3);
	lives_icon.setBitmap("resources/images/lives.png");
	
	
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
		else if(keys[KEY_DOWN])
			if(getY() == HEIGHT - bitmapHeight)
				dirY = 0;
			else
				dirY = 1;
		else dirY  = 0;
		// Horizontal movement
		if (keys[KEY_LEFT] && keys[KEY_RIGHT])
			dirX = 0;
		else if (keys[KEY_LEFT])
			if(getX() == 0)
				dirX = 0;
			else
				dirX = -1;
		else if (keys[KEY_RIGHT])
			if(getX() == WIDTH - bitmapWidth)
				dirX = 0;
			else
				dirX = 1;
		else dirX = 0;
	update();
}

void penguin::collision()
{
	lives--;
}

void penguin::draw()
{
	// draw everything else unique to penguin
	for(int i = 0; i < lives; i++)
	{
		al_draw_bitmap(lives_icon.getBitmapPointer(),al_get_bitmap_width(lives_icon.getBitmapPointer())*i, 0, 0);
	}
	object::draw();
}