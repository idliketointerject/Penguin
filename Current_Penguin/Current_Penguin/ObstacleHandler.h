#pragma once
#include "penguin.h"
#include "obstacle.h"
#include "Globals.h"
//#include "powerUp.h"

// Class to handle Obstacles

class obstacleHandler
{
public:
	obstacleHandler();
	obstacleHandler(char *bitmapPath);

	void update();
	bool checkCollision(penguin &obj);
	bool checkCollision(bullet bul[]);
	void draw();
	bool verifyBitmaps();
	void drawBoundingBoxes();
	void updateSpawn();
	void reset();

private:
	obstacle obstacles[NUM_OBSTACLES];
};