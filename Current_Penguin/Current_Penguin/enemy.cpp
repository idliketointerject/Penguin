#include "enemy.h"

Enemy::Enemy(){
	image = al_load_bitmap("resources/images/blowfish.png");
	flag = 1;
	counter = 0;
	hp = 100;
	hp_max = hp;
	bullet_time = 150;
	dirX = 1;
	dirY = 1;
}

void Enemy::enemy_pattern0(int i){
	int t = counter;
    if(t == 0 + 20*i)
        speedX = -3;	//Goes left
    if(t == 40 + 20*i)
        speedX = 0;	//Stops
    if(t == 40 + 240 + 20*i)	//Waits for a specified amount of time
        speedX = 3;	//Goes right
}

void Enemy::enemy_pattern1(int i){
    int t = counter;
    if(t == 20*i)
        speedX = -3;	//Goes left
    if(t == 40 + 20*i)
        speedX = 0;		//Stops
    if(t == 40 + 240 + 20*i){	//Waits for a specified amount of time
        speedY = -1;	//Moves up
        speedX = -2;	//and diagonally left
    }
}

void Enemy::enemy_pattern2(int i){
    int t = counter;
	if(i%2 == 1)
			dirY = -1; //Reverses direction for odd numbered enemies
    if(t == 20*i)
        speedX = -5;	//Moves left
    if(t > 30 + 20*i && 100 + 20*i){
        speedY -= 5/100.0;	//Accelerates up
        speedX += 5/100.0;	//Deccelerates 
    }
}

void Enemy::enemy_pattern3(int i){	//Moves diagonally up to the left
    int t = counter;
    if(t == 40*i){
        speedY -= 2;
        speedX = -4;
    }
}

void Enemy::enemy_enter(int i){
	if(counter == 0){
		hp = 100;
		hp_max = hp;
		x = WIDTH;
		//y = (HEIGHT/6) * (i + 1) - 50;
		y = HEIGHT/2 - 50;
		bullet_time = 150;
	}
}

void Enemy::enemy_act(int i){
	if(flag == 1){           //check if enemy is active
		enemy_pattern2(i);    //move according to pattern
		update();
		counter++;
		if(x < -100 || WIDTH + 50 < x || y < -100 || HEIGHT + 50 < y){   //if enemy leaves screen, deactivate
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