#include "enemy.h"

Enemy::Enemy(){
	bitmap = al_load_bitmap("resources/images/blowfish.png");
	flag = 1;
	counter = 0;
	hp = 100;
	hp_max = hp;
	x0 = 1366 + 20;
	y0 = 240;
	bullet_time = 150;
}

void Enemy::enemy_pattern0(){   //simple movement pattern where enemy comes from the right,
    if(counter < 60)			//stops, and then goes back out through the right again.
        x0 -= 4;
    if(counter > 60+240)
        x0 += 8;
}

/**void Enemy::enemy_enter(){
	if(ticks == 100){
		counter = 0;
		hp = 100;
		hp_max = hp;
		x0 = 700;
		y0 = 240;
		bullet_time = 150;
	}
}*/

void Enemy::enemy_act(){
	if(flag == 1){           //check if enemy is active
		enemy_pattern0();    //move according to pattern
		counter++;
		if(x0 < -50 || 1366 + 50 < x0 || y0 < -50 || 480 + 50 < y0)   //if enemy leaves screen, deactivate
			flag = 0;
		//if(bullet_time == counter)   //check whether it's time to fire bullets
		//	fire;
	}
}

void Enemy::fire(){

}

/**void Enemy::enemy_main(){
    enemy_enter();
    enemy_act();
}*/

void enemies_logic(Enemy enemy[]){
	int i;
	for (i=0; i<MAX_ENEMIES; i++)
		enemy[i].enemy_act();
}