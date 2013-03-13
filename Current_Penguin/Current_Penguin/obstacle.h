#pragma once
#include "Object.h"
#include "Utility.h"
#include "bullet.h"

class obstacle: public object
{
public:
	obstacle();
	obstacle(char * bitmapPath);

	void randYSpawn(int speed);
	virtual void update();

	void setSpawnConstant(int value);
	int getSpawnConstant() {return spawnConstant;}
	void setLives(int i){lives = i;}
	int getLives(){return lives;}
	void bulletCollision(){lives=lives-1; if(lives<1) collision();}
	bool checkBulletCollision(bullet &bul);
	void reset();
	void updateSpawn();

private:
	int spawnConstant; // this must be >= 1: gives a 1 in spawnConstant chance of spawning
	int lives;
};
