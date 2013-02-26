#ifndef PENGUIN_H
#define PENGUIN_H
#include "Object.h"

class penguin: public object{
public:
	penguin();
	penguin(char *bitmapPath);
	void move(bool keys[]);
	virtual void collision();
};
#endif
