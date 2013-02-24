#pragma once
#include "obstacle.h"
#include "Globals.h"

// Class to handle Obstacles

class obstacleHandler
{
public:
	obstacleHandler();
	obstacleHandler(char *bitmapPath);

	void update();
	void draw();
	bool verifyBitmaps();

private:
	obstacle obstacles[NUM_OBSTACLES];
};