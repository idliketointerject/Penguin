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

void penguin::setLives(int lives)
{
	penguin::lives = lives;
	if (penguin::lives < 0 )
	{
		penguin::lives = 0;
	}
}

void penguin::update()
{
	x += speedX * dirX;
	y += speedY * dirY;
	if ( x < 0 ) x = 0;
	else if ( x > WIDTH - bitmapWidth ) x = WIDTH - bitmapWidth;
	if ( y < 0 ) y = 0;
	else if ( y > HEIGHT - bitmapHeight ) y = HEIGHT - bitmapHeight;
}


void penguin::move(bool keys[]){
		// Vertical Movement
		if (keys[KEY_UP] && keys[KEY_DOWN])
			dirY = 0;
		else if(keys[KEY_UP])
			dirY = -1;
		else if(keys[KEY_DOWN])
			dirY = 1;
		else dirY  = 0;
		// Horizontal movement
		if (keys[KEY_LEFT] && keys[KEY_RIGHT])
			dirX = 0;
		else if (keys[KEY_LEFT])
			dirX = -1;
		else if (keys[KEY_RIGHT])
			dirX = 1;
		else dirX = 0;
	penguin::update();
}

void penguin::collision()
{
	// This function is what occures when any collision happens. Only those responses should go here
	fprintf(stderr, "%i", getLives());
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