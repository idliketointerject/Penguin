#include "enemy.h"

Enemy::Enemy(){
	setImage("resources/images/blowfish.png");
	flag = 1;
	counter = 0;
	hp = 2;
	hp_max = hp;
	bullet_time = 100;
	dirX = 1;
	dirY = 1;
	speed = 0;
	angle = 0;
	for(int i=0;i<SHOT_MAX;i++)
	{
		bullets[i].setImage("resources/images/enmBullet.png");
	}
	setValuesFromBitmap();
}

EnemMemFn enemy_pattern[ENEMY_PATTERN_MAX] = {&Enemy::enemy_pattern0, &Enemy::enemy_pattern1, &Enemy::enemy_pattern2, &Enemy::enemy_pattern3, &Enemy::enemy_pattern4, &Enemy::enemy_pattern5, &Enemy::enemy_pattern6, &Enemy::enemy_pattern7, &Enemy::enemy_pattern8};

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
        speedY = -2;	//Moves up
        speedX = -4;	//and diagonally left
    }
}

void Enemy::enemy_pattern2(int i){
    int t = counter;
    if(t == 20*i)
        speedX = -3;	//Goes left
    if(t == 40 + 20*i)
        speedX = 0;		//Stops
    if(t == 40 + 240 + 20*i){	//Waits for a specified amount of time
        speedY = 2;	//Moves down
        speedX = -4;	//and diagonally left
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
        speed=3;
    }
    if(t >= 100 + 30*i){
        speedX += 0.05;
    }
}

void Enemy::enemy_enter(int i, int random){
	if(counter == 0){
		hp = hp_max;
		x = WIDTH;
		if(random >= 0 && random <= 2)
			y = (HEIGHT/6) * (i + 1) - 50;
		else
			y = HEIGHT/2 - 50;
		bullet_time = 100;
		speedX = 0;
		speedY = 0;
		dirX = 1;
		dirY = 1;
		speed = 0;
		angle = 0;
	}
}

void Enemy::enemy_act(int i, int random, penguin &obj){
	if(flag == 1){           //check if enemy is active
		(this->*enemy_pattern[random])(i);    //move according to pattern
		update();
		counter++;
		if(x < -100 || WIDTH + 50 < x || y < -100 || HEIGHT + 50 < y){   //if enemy leaves screen, deactivate
			flag = 0;
		}
		if(counter == bullet_time + 20*i)   //check whether it's time to fire bullets
			fire(i);		//it's bullet time
	}
	for(int j = 0; j < SHOT_MAX - (3-difficulty); j++)
			bullets[j].logic(j, obj);
}

void Enemy::fire(int i){
	for(int j = 0; j < SHOT_MAX - (3-difficulty); j++){
		//bullets[j].setFlag(1);
		bullets[j].enter(x+float(bitmapWidth)/2, y+float(bitmapHeight)/2);
        bullets[j].setNum(i);	//num = which enemy bullet came from
    }
}

void Enemy::draw(){
	if(flag)
		object::draw();
	for(int i=0; i<SHOT_MAX - (3-difficulty); i++){
		if(bullets[i].flagUp())
			al_draw_bitmap(bullets[i].getImage(), bullets[i].getX(), bullets[i].getY(), 0);
	}
}

bool Enemy::checkCollision(penguin &obj)
{
	if ( !flag || !obj.isCollidable() )
	{
		return false;
	}
	if ( 
		x < obj.getX() + obj.getBoundX() - 1 &&
		y < obj.getY() + obj.getBoundY() - 1 &&
		x + boundX -1 > obj.getX() &&
		y + boundY - 1 > obj.getY() 
	   )
	{
		collision();
		flag = 0;
		counter = 0;
		obj.setLives(obj.getLives() - 1);
		return true;
	}

	return false;
}

bool Enemy::checkCollision(bullet bul[])
{
	bool check = false;
	for(int i=0; i<NUM_BULLETS;i++)
	{
		if (bul[i].isCollidable() && bul[i].isAlive())
		{
			if(checkBulletCollision(bul[i]))
			{
				collision();
				bul[i].collision();
				check = true;
			}
		}
	}
	return check;
}

bool Enemy::checkBulletCollision(bullet &bul)
{
	if ( !flag || !bul.isCollidable() )
	{
		return false;
	}
	if ( 
		x < bul.getX() + bul.getBoundX() - 1 &&
		y < bul.getY() + bul.getBoundY() - 1 &&
		x + boundX -1 > bul.getX() &&
		y + boundY - 1 > bul.getY() 
	   )
	{
		return true;
	}

	return false;
}

void Enemy::collision()
{
	hp--;
	if (hp == 0)
	{
		object::collision();
		flag = 0;
		counter = 0;
	}
}

void Enemy::reset()
{
	setFlag(0);
	for ( int i = 0; i < SHOT_MAX; i++)
	{
		bullets[i].setFlag(0);
	}
	difficulty = 0;
}

void Enemy::increaseDifficulty()
{
	if(difficulty < 3)
		difficulty = difficulty + 1;
}

int random;
void enemies_logic(Enemy enemy[], penguin &obj){
	if (allDead(enemy)){           //if the previous wave is dead, reset them to spawn in a new wave
		random = randInt(0, ENEMY_PATTERN_MAX);    //select a random movement pattern for the new wave
		for (int i=0; i<MAX_ENEMIES; i++){
			enemy[i].setCounter(0);
			enemy[i].setFlag(1);
		}
	}
	for (int i=0; i<MAX_ENEMIES; i++){
		enemy[i].enemy_enter(i, random);
		enemy[i].enemy_act(i, random, obj);
	}
}

bool allDead(Enemy enemy[]){
	for (int i=0; i<MAX_ENEMIES; i++){
		if(enemy[i].flagUp())
			return false;
	}
	return true;
}