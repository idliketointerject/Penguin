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
	if ( ( x + bitmapWidth ) <= 0 )
		x = 0;
}

void backGround::draw()
{
	object::draw();
	if( ( x + bitmapWidth ) < WIDTH )
		al_draw_bitmap(image,x+bitmapWidth,0,0);
}
//TODO: make drawScaled() work
void backGround::drawScaled()
{
	object::drawScaled();
	if( ( x + bitmapWidth ) < WIDTH ){
		//al_draw_bitmap(image,x+imageWidth,0,0);
		al_draw_scaled_bitmap(image,0,0, bitmapWidth, bitmapHeight, 0, 0, WIDTH, HEIGHT, 0);
	}
}

void backGround::drawYScaled()
{
	object::drawYScaled();
	if( ( x + bitmapWidth ) < WIDTH ){
		//al_draw_bitmap(image,x+imageWidth,0,0);
		al_draw_scaled_bitmap(image,0,0, bitmapWidth, bitmapHeight,x+bitmapWidth, y, bitmapWidth, HEIGHT, 0);
	}
}

void backGround::playMusic(char * songtitle){//this should probably be part of the object class, for obstacle noises
	sampleWrapper BGM(songtitle); 
	al_play_sample(BGM.getSamplePointer(), 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
}
