#include "obstacle.h"
#define DEFAULTSPAWN 500

obstacle::obstacle() : object()
{
	setSpawnConstant(DEFAULTSPAWN);
}

obstacle::obstacle(char * bitmapPath) : object(bitmapPath)
{
	setSpawnConstant(DEFAULTSPAWN);
}

void obstacle::reset()
{
	setSpawnConstant(DEFAULTSPAWN);
	setAlive(false);
}

void obstacle::updateSpawn()
{
	if(spawnConstant > 4)
		spawnConstant--;
}

void obstacle::randYSpawn(int speed)
{
	x = WIDTH;
	dirX = -1;
	speedX = speed;
	y = randInt(0,HEIGHT - bitmapHeight);
	setAlive(true);
	setCollidable(true);
	lives = HEALTH_OBSTACLE;
	boundX = bitmapWidth;
	boundY = bitmapHeight;
}

void obstacle::update()
{
	if (isAlive())
	{
		object::update();
		if ( x + bitmapWidth < 0 )
		{
			initAllToZero();
		}
		if(lives < 1)
		{
			initAllToZero();
		}
	}
	else // Give a chance to randomly spawn
	{
		if (randInt(1,spawnConstant) == 1 ) // 1 in 500 chance
		{
			randYSpawn(8);
		}
	}
}

void obstacle::setSpawnConstant(int value)
{
	if ( !(value < 1) )
	{
		spawnConstant = value;
	}
}

bool obstacle::checkBulletCollision(bullet &bul)
{
	if ( !isCollidable() || !bul.isCollidable() )
	{
		return false;
	}
	if ( 
		x < bul.getX() + bul.getBoundX() - 1 &&
		y < bul.getY() + bul.getBoundY() - 1 &&
		x + boundX -1 > bul.getX() &&
		y + boundY - 1 > bul.getY() 
	   )
	{
		bulletCollision();
		bul.collision();
		return true;
	}

	return false;
}