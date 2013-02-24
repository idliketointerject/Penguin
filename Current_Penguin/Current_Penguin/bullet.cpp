/*
#include "bullet.h"
#include "penguin.h"
#include "enemy.h"

Bullet::Bullet(){
	bitmap = al_load_bitmap("resources/images/bullet.png");
	flag = 1;
	counter = 0;
	x0 = 700;
	y0 = 240;
}

/**double Bullet::angleToPenguin(int n, penguin p, Enemy enm[]){
	return atan2(p.penguin_y-enm[num].y0,p.penguin_x-enm[num].x0);
}*/