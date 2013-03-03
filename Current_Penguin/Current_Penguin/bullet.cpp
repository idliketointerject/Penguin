#include "bullet.h"

bullet::bullet() :object()
{
	initAllToZero();
}

void bullet::reset(float x, float y)
{
	setX(x);
	setY(y);
	setAlive(true);
	setCollidable(true);
}

void bullet::prepare(int dirx, int diry, float spex, float spey)
{
	setDirX(dirx);
	setDirY(diry);
	setSpeedX(spex);
	setSpeedY(spey);
	setAlive(true);
	setCollidable(true);
}

void bullet::checkCollision(object &obj)
{
	if ( !isCollidable() || !obj.isCollidable() || !isAlive() || !obj.isAlive())
	{
		return;
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
		return;
	}
}