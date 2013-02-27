#include "enemy.h"

Enemy::Enemy(){
	setImage("resources/images/blowfish.png");
	flag = 1;
	counter = 0;
	hp = 100;
	hp_max = hp;
	bullet_time = 150;
	dirX = 1;
	dirY = 1;
	speed = 0;
	angle = 0;
}

EnemMemFn enemy_pattern[ENEMY_PATTERN_MAX] = {&Enemy::enemy_pattern0, &Enemy::enemy_pattern1, &Enemy::enemy_pattern2, &Enemy::enemy_pattern3, &Enemy::enemy_pattern4, &Enemy::enemy_pattern5, &Enemy::enemy_pattern6, &Enemy::enemy_pattern7, &Enemy::enemy_pattern8};
//void (Enemy::*enemy_pattern[4])(int i) = {&Enemy::enemy_pattern0, &Enemy::enemy_pattern1, &Enemy::enemy_pattern2, &Enemy::enemy_pattern3};

double randAng(double ang){
    return ( -ang + ang*2 * randInt(0, 10000)/10000.0 );
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
    if(t == 20*i)
        speedX = -3;	//Goes left
    if(t == 40 + 20*i)
        speedX = 0;		//Stops
    if(t == 40 + 240 + 20*i){	//Waits for a specified amount of time
        speedY = 1;	//Moves down
        speedX = -2;	//and diagonally left
    }
}

void Enemy::enemy_pattern3(int i){
    int t = counter;
    if(t == 20*i)
        speedX = -5;	//Moves left
    if(t > 30 + 20*i && 100 + 20*i){
        speedY -= 5/100.0;	//Accelerates up
        speedX += 5/100.0;	//Deccelerates left
    }
}

void Enemy::enemy_pattern4(int i){
    int t = counter;
    if(t == 20*i)
        speedX = -5;	//Moves left
    if(t > 30 + 20*i && 100 + 20*i){
        speedY += 5/100.0;	//Accelerates down
        speedX += 5/100.0;	//Deccelerates left
    }
}

void Enemy::enemy_pattern5(int i){
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

void Enemy::enemy_pattern6(int i){	//Moves diagonally up to the left
    int t = counter;
    if(t == 40*i){
        speedY -= 2;
        speedX = -4;
    }
}

void Enemy::enemy_pattern7(int i){	//Moves diagonally down to the left
    int t = counter;
    if(t == 40*i){
        speedY += 2;
        speedX = -4;
    }
}

void Enemy::enemy_pattern8(int i){
    int t=counter;
    if(t == 0 + 20*i) speedX = -6;	//Goes left
    if(t == 40 + 20*i) speedX = 0;	//Stops
    if(t >= 40 + 20*i){
        if(t%60 == 0){
            int r=cos(angle)< 0 ? 0 : 1;
            speed=6+randAng(2);
            angle=randAng(PI/4)+PI*r;
        }
        speed=2;
    }
    if(t >= 100 + 30*i){
        speedX += 0.05;
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
		speedX = 0;
		speedY = 0;
		dirX = 1;
		dirY = 1;
		speed = 0;
		angle = 0;
	}
}

void Enemy::enemy_act(int i, int random){
	if(flag == 1){           //check if enemy is active
		(this->*enemy_pattern[random])(i);    //move according to pattern
		//update();
		x += cos(angle)*speed;
        y += sin(angle)*speed;
        x += speedX;
        y += speedY * dirY;
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

int random = 8;
void enemies_logic(Enemy enemy[]){
	if (enemy[4].flagUp() == 0){
		random = randInt(0, ENEMY_PATTERN_MAX-1);
		for (int i=0; i<MAX_ENEMIES; i++){
			enemy[i].setCounter(0);
			enemy[i].setFlag(1);
		}
	}
	for (int i=0; i<MAX_ENEMIES; i++){
		enemy[i].enemy_enter(i);
		enemy[i].enemy_act(i, random);
	}
}