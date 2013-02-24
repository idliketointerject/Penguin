#include "obstacle.h"
#define DEFAULTSPAWN 500
/*
int obstacle::bounding_box_collision(int b1_x, int b1_y, int b1_w, int b1_h, int b2_x, int b2_y, int b2_w, int b2_h)
{
    if ((b1_x > b2_x + b2_w - 1) || // is b1 on the right side of b2?
        (b1_y > b2_y + b2_h - 1) || // is b1 under b2?
        (b2_x > b1_x + b1_w - 1) || // is b2 on the right side of b1?
        (b2_y > b1_y + b1_h - 1))   // is b2 under b1?
    {
        // no collision
        return 0;
    }
 
    // collision
    return 1;
}
*/

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