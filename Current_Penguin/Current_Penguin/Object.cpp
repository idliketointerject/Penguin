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
	setAlive(false);
	setCollidable(false);
}

object::object(float x, float y, float speedX, float speedY, int dirX, int dirY, int boundX,
	int boundY, char *bitmapPath, bool alive, bool collidable)
{
	setX(x);
	setY(y);
	setSpeedX(speedX);
	setSpeedY(speedY);
	setDirX(dirX);
	setDirY(dirY);
	setBoundX(boundX);
	setBoundY(boundY);
	setImage(bitmapPath);
	setValuesFromBitmap();
	setAlive(alive);
	setCollidable(collidable);
}

object::object(char *bitmapPath)
{
	setImage(bitmapPath);
}

void object::setValuesFromBitmap()
{
	bitmapHeight = al_get_bitmap_height(wBitmap.getBitmapPointer());
	bitmapWidth = al_get_bitmap_width(wBitmap.getBitmapPointer());
}

bool object::setImage(char *path)
{
	if (wBitmap.setBitmap(path))
	{
		setValuesFromBitmap();
		return true;
	}
	return false;
}

void object::draw()
{
	al_draw_bitmap(wBitmap.getBitmapPointer(), x, y, 0);
}

void object::drawScaled()
{
	al_draw_scaled_bitmap(wBitmap.getBitmapPointer(),0,0, bitmapWidth, bitmapHeight, x, y, WIDTH, HEIGHT, 0);
}

void object::drawYScaled()
{
	al_draw_scaled_bitmap(wBitmap.getBitmapPointer(),0,0,bitmapWidth, bitmapHeight,x,y,bitmapWidth,HEIGHT,0);
}

void object::update()
{
	x += speedX * dirX;
	y += speedY * dirY;
}