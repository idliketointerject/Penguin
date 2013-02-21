//creates background class which inherits object, and will be used to make a background object that scrolls accross the screen in main
#pragma once
#include "backGround.h"
#include "Object.h"
#include "initAllegro.h"

backGround::backGround(){

	//bitmapWrapper bgimage("resources/images/background.jpg");
	//setImage(bgimage.getBitmapPointer());
	//object(WIDTH,0,10.0,0,-1,0,bgimage.getBitmapWidth(),0,bgimage.getBitmapPointer(),false,false);
	/*setX(WIDTH);
	setY(0);
	setSpeedX(10.0);
	setSpeedY(0);
	setDirX(-1);
	setDirY(0);
	setBoundX(bgimage.getBitmapWidth());
	setBoundY(0);
	setImage(bgimage.getBitmapPointer());
	setAlive(false);
	setCollidable(false);
	*/
}

void backGround::scrollBackGround(){
	int scrollLimit = al_get_bitmap_width( image );

	x--;
	//x + scrolLimit < 0
	if(x + scrollLimit < 0){
		x = WIDTH;
	}
	scrollLimit--;
	update();
}

void backGround::playMusic(char * songtitle){//this should probably be part of the object class, for obstacle noises
	sampleWrapper BGM(songtitle); 
	al_play_sample(BGM.getSamplePointer(), 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
}
