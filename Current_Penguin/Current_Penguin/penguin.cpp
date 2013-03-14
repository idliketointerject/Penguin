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
	for(int i=0;i<NUM_BULLETS;i++)
	{
		bullets[i].setImage("resources/images/bullet.png");
	}
}

void penguin::reset()
{
	setLives(3);
	setX(0);
	setY(HEIGHT/2 + bitmapHeight /2);
	setSpeedX(10.0);
	setSpeedY(10.0);
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
	updateBullets();
	x += speedX * dirX;
	y += speedY * dirY;
	if ( x < 0 ) x = 0;
	else if ( x > WIDTH - bitmapWidth ) x = WIDTH - bitmapWidth;
	if ( y < 0 ) y = 0;
	else if ( y > HEIGHT - bitmapHeight ) y = HEIGHT - bitmapHeight;
}


void penguin::move(bool keys[]){
	// Shoot, if space is pressed.
		if (keys[KEY_SPACE])
			spawnBullet();	
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

void penguin::spawnBullet()
{
	for(int i=0;i<NUM_BULLETS;i++)
	{
		if(!bullets[i].isAlive())
		{
			bullets[i].reset(x+float(bitmapWidth)/2,y+float(bitmapHeight)/2);
			//can be replaced later with power up affected bullet values for speed.
			bullets[i].prepare(1,0,8.0,8.0);
			return;
		}
	}
}

void penguin::updateBullets()
{
	for(int i=0;i<NUM_BULLETS;i++)
	{
		bullets[i].update();
		if(bullets[i].getX()>WIDTH+float(bullets[i].getBitmapWidth())/2)
			bullets[i].setAlive(false);
	}	
}

void penguin::draw()
{
	for(int i=0;i<NUM_BULLETS;i++)
	{
		if(bullets[i].isAlive())
		al_draw_bitmap(bullets[i].getImage(), bullets[i].getX(), bullets[i].getY(), 0);
	}
	// draw everything else unique to penguin
	for(int i = 0; i < lives; i++)
	{
		al_draw_bitmap(lives_icon.getBitmapPointer(),al_get_bitmap_width(lives_icon.getBitmapPointer())*i, 0, 0);
	}
	object::draw();
}