#include "draw.h"

void draw_enemies(Enemy enemy[]){
	int i;
	for (i=0; i<MAX_ENEMIES; i++){
		if(enemy[i].flag == 1)			//check which enemies are active
			al_draw_bitmap(enemy[i].bitmap,enemy[i].x0,enemy[i].y0,0);
	}
}

void draw_bullets(Bullet bullet[]){
	int i;
	for (i=0; i<MAX_BULLETS; i++){
		if(bullet[i].flag == 1)			//check which enemies are active
			al_draw_bitmap(bullet[i].bitmap,bullet[i].x0,bullet[i].y0,0);
	}
}