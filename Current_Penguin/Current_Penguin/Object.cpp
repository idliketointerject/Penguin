#include "Object.h"

//Constructors
object::object()
{
	setX(0);
	setY(0);
	setSpeedX(0);
	setSpeedY(0);
	setDirX(0);
	setDirY(0);
	setBoundX(0);
	setBoundY(0);
	setImage(NULL);
	setAlive(false);
	setCollidable(false);
}

object::object(float x, float y, float speedX, float speedY, int dirX, int dirY, int boundX,
	int boundY, ALLEGRO_BITMAP *image, bool alive, bool collidable)
{
	setX(x);
	setY(y);
	setSpeedX(speedX);
	setSpeedY(speedY);
	setDirX(dirX);
	setDirY(dirY);
	setBoundX(boundX);
	setBoundY(boundY);
	setImage(image);
	setAlive(alive);
	setCollidable(collidable);
}

void object::draw()
{
	al_draw_bitmap(image, x, y, 0);
}

void object::drawScaled()
{
	al_draw_scaled_bitmap(image,0,0, getBitmapWidth(), getBitmapHeight(), x, y, WIDTH, HEIGHT, 0);
}

void object::drawYScaled()
{
	al_draw_scaled_bitmap(image,0,0,bitmapWidth, bitmapHeight,x,y,bitmapWidth,HEIGHT,0);
}

void object::update()
{
	x += speedX * dirX;
	y += speedY * dirY;
}