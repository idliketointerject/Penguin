#include "powerUp.h"
#define DEFAULTSPAWN 5000
healthPowerUp::healthPowerUp(): obstacle()
{
	setSpawnConstant(DEFAULTSPAWN);
}

healthPowerUp::healthPowerUp(char * bitmapPath): obstacle(bitmapPath)
{
	setSpawnConstant(DEFAULTSPAWN);
}

void healthPowerUp::modifyAttributes(penguin p, obstacleHandler x){
	if (x.checkCollision(p)){
		//increase health, if health is not > 3
		if(p.getLives() < 3){
			p.setLives(p.getLives() + 1);
		}
	}
}


speedPowerUp::speedPowerUp(): obstacle()
{
	setSpawnConstant(DEFAULTSPAWN);
}

speedPowerUp::speedPowerUp(char * bitmapPath): obstacle(bitmapPath)
{
	setSpawnConstant(DEFAULTSPAWN);
}

void speedPowerUp::modifyAttributes(){

}