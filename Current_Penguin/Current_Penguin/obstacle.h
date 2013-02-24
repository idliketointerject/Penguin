#pragma once
#include "Object.h"
#include "Utility.h"

class obstacle: public object
{
public:
	obstacle();
	obstacle(char * bitmapPath);

	void randYSpawn(int speed);
	virtual void update();

	void setSpawnConstant(int value);
	int getSpawnConstant() {return spawnConstant;}
private:
	int spawnConstant; // this must be >= 1: gives a 1 in spawnConstant chance of spawning
};
