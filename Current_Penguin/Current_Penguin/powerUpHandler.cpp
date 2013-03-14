#pragma once
#include "powerUpHandler.h"


powerUpHandler::powerUpHandler(char *bitmapPath)
{
	for( int i = 0; i < NUM_OBSTACLES; i++ )
	{
		health[i].setImage(bitmapPath);
	}
}

void powerUpHandler::update()
{
	for( int i = 0; i < NUM_OBSTACLES; i++ )
	{
		health[i].update();
	}
}

void powerUpHandler::reset()
{
	for( int i = 0; i < NUM_OBSTACLES; i++)
	{
		health[i].reset();
		speed[i].reset();
	}
}

void powerUpHandler::draw()
{
	for( int i = 0; i < NUM_OBSTACLES; i++ )
	{
		if (health[i].isAlive())
		{
			health[i].draw();
		}
	}
}

bool powerUpHandler::verifyBitmaps()
{
	for( int i = 0; i < NUM_OBSTACLES; i++ )
	{
		if(!health[i].verifyBitmap())
			return false;
	}
	return true;
}

bool powerUpHandler::checkCollision(object &obj)
{
	if (!obj.isCollidable() || !obj.isAlive()) return false;
	bool check = false;
	for ( int i = 0; i < NUM_OBSTACLES; i++ )
	{
		if ( !health[i].isCollidable() || !health[i].isAlive() ) continue;
		if ( health[i].checkCollision(obj) )
		{
			check = true;
		}
	}
	return check;
}

void powerUpHandler::drawBoundingBoxes()
{
	for( int i = 0; i < NUM_OBSTACLES; i++ )
	{
		if (health[i].isAlive())
			health[i].drawBoundingBox();
	}
}


void powerUpHandler::checkHealthCollision(penguin &obj)
{
	bool check = false;
	for ( int i = 0; i < NUM_OBSTACLES; i++ )
	{
		if ( !health[i].isCollidable() || !health[i].isAlive() ) continue;
		if ( health[i].checkCollision(obj) )
		{
			check = true;
			if(obj.getLives() < 3){
				obj.setLives(obj.getLives() + 1);
			}
		}

	}
}

void powerUpHandler::checkSpeedCollision(penguin &obj)
{
	bool check = false;
	for(int i = 0; i < NUM_OBSTACLES;i++)
	{
		if ( !health[i].isCollidable() || !health[i].isAlive() ) continue;
		if ( health[i].checkCollision(obj) )
		{
			check = true;
			if(obj.getSpeedX() < 50.0){
				obj.setSpeedX(obj.getSpeedX() + 2.0);
			}
			if(obj.getSpeedY() < 50.0){
				obj.setSpeedY(obj.getSpeedY() + 2.0);
			}
		}

	}
}

bool powerUpHandler::checkCollision(bullet bul[])
{
	bool check = false;
	for(int i=0; i<NUM_BULLETS;i++)
	{
		if (bul[i].isCollidable() && bul[i].isAlive())
		{
			for ( int j = 0; j < NUM_OBSTACLES; j++ )
			{
				if ( health[j].isCollidable() && health[j].isAlive() )
				{
					if ( health[j].checkCollision(bul[i]) )
					{
						check = true;
					}
				}
				if ( speed[j].isCollidable() && speed[j].isAlive() )
				{
					if ( speed[j].checkCollision(bul[i]) )
					{
						check = true;
					}
				}
			}
		}
	}
	return check;
}