#ifndef BULLET_H
#define BULLET_H
#include "Object.h"

class bullet: public object{
public:
	bullet();
	void reset(float x, float y);
	void prepare(int dirx, int diry, float spex, float spey);
	void checkCollision(object &ob);
};
#endif
