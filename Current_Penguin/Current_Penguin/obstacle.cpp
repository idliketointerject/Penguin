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

void obstacle::randYSpawn(int speed)
{
	x = WIDTH;
	dirX = -1;
	speedX = speed;
	y = randInt(0,HEIGHT - bitmapHeight);
	setAlive(true);
	setCollidable(true);
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