#ifndef ENMBULLET_H
#define ENMBULLET_H
#include "Utility.h"
#include "Object.h"
#include "bullet.h"
#include "penguin.h"

class EnmBullet : public object{
public:
	EnmBullet();
	void enter(int enemyX, int enemyY);
	void checkOnScreen();
	void logic(int j, penguin &obj);
	void setFlag(int n){flag = n;};
	void setNum(int n){enm_num = n;};
	int flagUp(){return flag;};
	bool checkCollision(penguin &obj);
private:
	int flag;			//1 if bullet is active, 0 if not on screen.
	int counter;		//time elapsed since bullet was fired
	int enm_num;		//which enemy in the wave the bullet was fired from
};
#endif