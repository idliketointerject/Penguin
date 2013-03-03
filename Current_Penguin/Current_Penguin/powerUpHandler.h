#pragma once
#include "powerUp.h"
#include "Globals.h"
//#include "powerUp.h"

// Class to handle powerUps

class powerUpHandler
{
public:
	powerUpHandler();
	powerUpHandler(char *bitmapPath);

	void update();
	bool checkCollision(object &obj);
	void draw();
	bool verifyBitmaps();
	void drawBoundingBoxes();
	void modifyLifeAttribute(penguin p);
	void modifySpeedAttribute(penguin p);
	void checkHealthCollision(penguin &obj);
	void checkSpeedCollision(penguin &obj);
	bool checkCollision(bullet bul[]);

private:
	healthPowerUp health[NUM_OBSTACLES];
	speedPowerUp speed[NUM_OBSTACLES];
};