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

void powerUpHandler::draw()
{
	for( int i = 0; i < NUM_OBSTACLES; i++ )
	{
		if (health[i].isAlive())
			health[i].draw();
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