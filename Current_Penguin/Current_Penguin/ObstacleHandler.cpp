#pragma once

#include "ObstacleHandler.h"

obstacleHandler::obstacleHandler()
{

}

obstacleHandler::obstacleHandler(char *bitmapPath)
{
	for( int i = 0; i < NUM_OBSTACLES; i++ )
	{
		obstacles[i].setImage(bitmapPath);
	}
}

void obstacleHandler::reset()
{
	for( int i = 0; i < NUM_OBSTACLES; i++)
	{
		obstacles[i].reset();
	}
}

void obstacleHandler::updateSpawn()
{
	for( int i = 0; i < NUM_OBSTACLES; i++)
	{
		obstacles[i].updateSpawn();
	}
}

void obstacleHandler::update()
{
	for( int i = 0; i < NUM_OBSTACLES; i++ )
	{
		obstacles[i].update();
	}
}

void obstacleHandler::draw()
{
	for( int i = 0; i < NUM_OBSTACLES; i++ )
	{
		if (obstacles[i].isAlive())
		{
			obstacles[i].draw();
		}
		
	}
}

bool obstacleHandler::verifyBitmaps()
{
	for( int i = 0; i < NUM_OBSTACLES; i++ )
	{
		if(!obstacles[i].verifyBitmap())
			return false;
	}
	return true;
}

bool obstacleHandler::checkCollision(penguin &obj)
{
	if (!obj.isCollidable() || !obj.isAlive()) return false;
	bool check = false;
	for ( int i = 0; i < NUM_OBSTACLES; i++ )
	{
		if ( !obstacles[i].isCollidable() || !obstacles[i].isAlive() ) continue;
		if ( obstacles[i].checkCollision(obj) )
		{
			obj.setLives(obj.getLives() - 1);
			check = true;
		}
	}
	return check;
}

bool obstacleHandler::checkCollision(bullet bul[])
{
	bool check = false;
	for(int i=0; i<NUM_BULLETS;i++)
	{
		if (bul[i].isCollidable() && bul[i].isAlive())
		{
			for ( int j = 0; j < NUM_OBSTACLES; j++ )
			{
				if ( obstacles[j].isCollidable() && obstacles[j].isAlive() )
				if ( obstacles[j].checkBulletCollision(bul[i]) )
				{
					obstacles[j].setLives(obstacles[j].getLives() - 1);
					check = true;
				}
			}
		}
	}
	return check;
}

void obstacleHandler::drawBoundingBoxes()
{
	for( int i = 0; i < NUM_OBSTACLES; i++ )
	{
		if (obstacles[i].isAlive())
			obstacles[i].drawBoundingBox();
	}
}