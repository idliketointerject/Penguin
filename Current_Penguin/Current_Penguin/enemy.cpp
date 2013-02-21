#include "enemy.h"

Enemy::Enemy(){
	bitmap = al_load_bitmap("resources/images/blowfish.png");
	flag = 1;
	counter = 0;
	hp = 100;
	hp_max = hp;
	bullet_time = 150;
}

void Enemy::enemy_pattern0(int i){   //simple movement pattern where enemy comes from the right, stops, and then goes back out through the right again.
	if(counter >= 20*i && counter < 60 + 20*i)			
        x0 -= 4;
    if(counter > 60+240 + 20*i)
        x0 += 8;
}

void Enemy::enemy_enter(int i){
	if(counter == 0){
		hp = 100;
		hp_max = hp;
		x0 = WIDTH +50;
		y0 = (HEIGHT/6) * (i + 1) - 50;
		bullet_time = 150;
	}
}

void Enemy::enemy_act(int i){
	if(flag == 1){           //check if enemy is active
		enemy_pattern0(i);    //move according to pattern
		counter++;
		if(x0 < -50 || WIDTH + 50 < x0 || y0 < -50 || HEIGHT + 50 < y0){   //if enemy leaves screen, deactivate
			flag = 0;
		//if(bullet_time == counter)   //check whether it's time to fire bullets
		//	fire;
		}
	}
}

void Enemy::fire(){

}

void enemies_logic(Enemy enemy[]){
	for (int i=0; i<MAX_ENEMIES; i++){
		enemy[i].enemy_enter(i);
		enemy[i].enemy_act(i);
	}
}