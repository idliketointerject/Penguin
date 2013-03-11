#ifndef PENGUIN_H
#define PENGUIN_H
#include "Object.h"
#include "bullet.h"
//#include "enmBullet.h"

class penguin: public object{
public:
	penguin();
	penguin(char *bitmapPath);
	void move(bool keys[]);
	virtual void update();
	virtual void draw();
	virtual void collision();
	void setLives(int lives);
	int getLives(){return lives;};
	void spawnBullet();
	void updateBullets();
	bullet * getBulletArray() {return bullets;};
private:
	int lives;
	bullet bullets[NUM_BULLETS];
	bitmapWrapper lives_icon;
};
#endif
