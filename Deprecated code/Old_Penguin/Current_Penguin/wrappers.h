#ifndef WRAPPERS_H
#define WRAPPERS_H
#include "initAllegro.h"

class bitmapWrapper
{
public:
	bitmapWrapper(char * path);
	~bitmapWrapper();
	//need to get the width of bitmap to determine scrolling
	int getBitmapWidth(){ return al_get_bitmap_width(getBitmapPointer());};
	bool verifyInitialization();
	ALLEGRO_BITMAP * getBitmapPointer();
private:
	ALLEGRO_BITMAP * bitmapPointer;
};

class displayWrapper
{
public:
	displayWrapper(int dWidth, int dHeight);
	~displayWrapper();
	bool verifyInitialization();
	ALLEGRO_DISPLAY * getDisplayPointer();
private:
	ALLEGRO_DISPLAY * displayPointer;
};

class timerWrapper
{
public:
	timerWrapper( int fps );
	~timerWrapper();
	bool verifyInitialization();
	ALLEGRO_TIMER * getTimerPointer();
private:
	ALLEGRO_TIMER * timerPointer;
};

class eventQueueWrapper
{
public:
	eventQueueWrapper();
	~eventQueueWrapper();
	bool verifyInitialization();
	ALLEGRO_EVENT_QUEUE * getEventQueuePointer();
private:
	ALLEGRO_EVENT_QUEUE * eventQueuePointer;
};

class sampleWrapper
{
public:
	sampleWrapper(char * path);
	~sampleWrapper();
	bool verifyInitialization();
	ALLEGRO_SAMPLE * getSamplePointer();
private:
	ALLEGRO_SAMPLE * samplePointer;
};

 
#endif