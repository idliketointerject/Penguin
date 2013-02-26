#include "Object.h"

//Constructors
object::object()
{
	initAllToZero();
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
	initAllToZero();
	setImage(bitmapPath);
}

void object::initAllToZero()
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

void object::setValuesFromBitmap()
{
	bitmapHeight = al_get_bitmap_height(wBitmap.getBitmapPointer());
	bitmapWidth = al_get_bitmap_width(wBitmap.getBitmapPointer());
	// for now also set bounding boxes
	boundX = bitmapWidth;
	boundY = bitmapHeight;
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

bool object::checkCollision(object &obj)
{
	if ( !isCollidable() || !obj.isCollidable() )
	{
		return false;
	}
	if ( 
		x < obj.getX() + obj.getBoundX() - 1 &&
		y < obj.getY() + obj.getBoundY() - 1 &&
		x + boundX -1 > obj.getX() &&
		y + boundY - 1 > obj.getY() 
	   )
	{
		collision();
		obj.collision();
		return true;
	}

	return false;
}

void object::collision()
{
	initAllToZero();
}

// for testing

void object::drawBoundingBox()
{
	al_draw_filled_rectangle(x,y,x + boundX - 1,y + boundY - 1,al_map_rgb(0,0,0));
}