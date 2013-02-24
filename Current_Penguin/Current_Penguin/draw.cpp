/*
#include "draw.h"

void draw_enemies(Enemy enemy[]){
	for (int i=0; i<MAX_ENEMIES; i++){
		if(enemy[i].flagUp() == 1)			//check which enemies are active
			al_draw_bitmap(enemy[i].getImage(), enemy[i].getX(), enemy[i].getY(), 0);
	}
}

void draw_bullets(Bullet bullet[]){
	for (int i=0; i<MAX_BULLETS; i++){
		if(bullet[i].flag == 1)			//check which enemies are active
			al_draw_bitmap(bullet[i].bitmap, bullet[i].x0, bullet[i].y0, 0);
	}
}
*/