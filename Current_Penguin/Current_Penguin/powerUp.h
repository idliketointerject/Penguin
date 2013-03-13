#include "obstacle.h"
#include "Utility.h"
#include "penguin.h"
#include "ObstacleHandler.h"

class healthPowerUp: public obstacle{
public:
	healthPowerUp();
	healthPowerUp(char * bitmapPath);
	//void randYSpawn(int speed);
	//void setSpawnProb(int value);
	//int getSpawnProb() {return spawnProb;}
	void modifyAttributes(penguin p, obstacleHandler x);
	void reset();

private:
	int lifeModifier;
	//int spawnProb;
};

class speedPowerUp: public obstacle{
public:
	speedPowerUp();
	speedPowerUp(char * bitmapPath);
	//void randYSpawn(int speed);
	//void setSpawnProb(int value);
	//int getSpawnProb() {return spawnProb;}
	void modifyAttributes();
	void reset();

private:
	float speedMod;
	//int spawnProb;
};


