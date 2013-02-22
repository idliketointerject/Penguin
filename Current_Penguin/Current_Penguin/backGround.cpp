//creates background class which inherits object, and will be used to make a background object that scrolls accross the screen in main
#pragma once
#include "backGround.h"
#include "Object.h"
#include "initAllegro.h"

backGround::backGround()
{
	object::object();
}

backGround::backGround(char *bitmapPath)
{
	setImage(bitmapPath);
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
		al_draw_bitmap(wBitmap.getBitmapPointer(),x+bitmapWidth,0,0);
}
//TODO: make drawScaled() work
void backGround::drawScaled()
{
	object::drawScaled();
	if( ( x + bitmapWidth ) < WIDTH ){
		//al_draw_bitmap(image,x+imageWidth,0,0);
		al_draw_scaled_bitmap(wBitmap.getBitmapPointer(),0,0, bitmapWidth, bitmapHeight, 0, 0, WIDTH, HEIGHT, 0);
	}
}

void backGround::drawYScaled()
{
	object::drawYScaled();
	if( ( x + bitmapWidth ) < WIDTH ){
		//al_draw_bitmap(image,x+imageWidth,0,0);
		al_draw_scaled_bitmap(wBitmap.getBitmapPointer(),0,0, bitmapWidth, bitmapHeight,x+bitmapWidth, y, bitmapWidth, HEIGHT, 0);
	}
}
