//creates background class which inherits object, and will be used to make a background object that scrolls accross the screen in main
#pragma once
#include "Object.h"
#include "Globals.h"

class backGround: public object{
public:
	backGround();
	backGround(char * bitmapPath);
	virtual void update();
	void draw();
	void drawScaled();
	void drawYScaled();
 
};