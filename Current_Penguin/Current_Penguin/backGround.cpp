//creates background class which inherits object, and will be used to make a background object that scrolls accross the screen in main
#pragma once
#include "backGround.h"
#include "Object.h"
#include "initAllegro.h"

backGround::backGround()
{
	object::object();
}

void backGround::update()
{
	object::update();
	if ( ( x + al_get_bitmap_width( image ) ) <= 0 )
		x = 0;
}

void backGround::draw()
{
	int imageWidth = al_get_bitmap_width( image );
	object::draw();
	if( ( x + imageWidth ) < WIDTH )
		al_draw_bitmap(image,x+imageWidth,0,0);
}

void backGround::playMusic(char * songtitle){//this should probably be part of the object class, for obstacle noises
	sampleWrapper BGM(songtitle); 
	al_play_sample(BGM.getSamplePointer(), 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
}