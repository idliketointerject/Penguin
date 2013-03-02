#ifndef PENGUIN_H
#define PENGUIN_H
#include "Object.h"

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

private:
	int lives;
	bitmapWrapper lives_icon;

};
#endif
