#ifndef ENEMY_H
#define ENEMY_H

#include "obstacle.h"
#include "penguin.h"
#include "enmBullet.h"
#include "initgame.h"
#include "Globals.h"
#include "Utility.h"

#define MAX_ENEMIES 5
#define ENEMY_PATTERN_MAX 9
#define SHOT_MAX 4

class Enemy : public object{
	public:
		Enemy();
		void enemy_pattern0(int i);
		void enemy_pattern1(int i);
		void enemy_pattern2(int i);
		void enemy_pattern3(int i);
		void enemy_pattern4(int i);
		void enemy_pattern5(int i);
		void enemy_pattern6(int i);
		void enemy_pattern7(int i);
		void enemy_pattern8(int i);
		void enemy_enter(int i);		//resets and initializes enemy information to spawn in a new wave
		void enemy_act(int i, int rand, penguin &obj);         //logic to call in main event loop
		void fire(int i);
		void draw();
		int flagUp(){return flag;};
		void setFlag(int n){flag = n;};
		int getCounter(){return counter;};
		void setCounter(int cnt){counter = cnt;};
		bool checkCollision(penguin &obj);
		bool checkCollision(bullet bul[]);
		bool checkBulletCollision(bullet &bul);
		void collision();
		void reset();
		EnmBullet * getEnmBulletArray() {return bullets;}
	private:
		int flag;			//1 if enemy is active, 0 if not on screen. Only enemies with flag == 1 are drawn by draw_enemies()
		int counter;		//time elapsed since enemy spawned
		int hp;
		int hp_max;
		int item;			//what item the enemy drops
		int bullet_time;	//when enemy should start firing
		EnmBullet bullets[SHOT_MAX];
};

typedef  void (Enemy::*EnemMemFn)(int i);
void enemies_logic(Enemy enemy[], penguin &obj);

#endif