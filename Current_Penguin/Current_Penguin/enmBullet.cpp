#include "enmBullet.h"

EnmBullet::EnmBullet() : object(){
	initAllToZero();
	flag = 0;
	setImage("resources/images/enmBullet.png");
}

void EnmBullet::enter(int enemyX, int enemyY){
	flag = 1;
	counter = 0;
	x = enemyX;
	y = enemyY;
//	setValuesFromBitmap();
}

void EnmBullet::checkOnScreen(){
	if(x < -100 || WIDTH + 50 < x || y < -100 || HEIGHT + 50 < y){   //if enemy leaves screen, deactivate
		flag = 0;
	}
}

void EnmBullet::logic(int j, penguin &obj){
	if(flag){
		int t = counter;
		if(t >= 30*j){
			if(t == 30*j)
				angle = ( atan2(obj.getY() - y, obj.getX() - x) );
			speed = 7;
			}
		counter++;
        update();
		checkOnScreen();
		checkCollision(obj);
	}
}

bool EnmBullet::checkCollision(penguin &obj)
{
	if ( !flag || !obj.isCollidable() )
	{
		return false;
	}
	if ( 
		x < obj.getX() + obj.getBoundX() - 1 &&
		y < obj.getY() + obj.getBoundY() - 1 &&
		x + boundX -1 > obj.getX() &&
		y + boundY - 1 > obj.getY() 
	   )
	{
		collision();
		flag = 0;
		counter = 0;
		obj.setLives(obj.getLives() - 1);
		return true;
	}

	return false;
}