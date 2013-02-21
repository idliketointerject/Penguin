#pragma once
#include "initAllegro.h"

class screenprinter
{
public:
	screenprinter(char * name);
	~screenprinter();
	ALLEGRO_FONT * getFontPointer();
	void setTextSize(int x){textSize = x;};
	int getTextSize(){return textSize;};
	void printText(char* message);
	int getXPos(){return XPos;};
	int getYPos(){return YPos;};
	void setXPos(int x){XPos = x;};
	void setYPos(int y){YPos = y;};
private:
	ALLEGRO_FONT * fontPointer;
	int textSize;
	int XPos;
	int YPos;
	char* fontName;
};