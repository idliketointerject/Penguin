#include "obstacle.h"
#include "initgame.h"
#include "Globals.h"

#define MAX_ENEMIES 5

class Enemy : public obstacle{
	public:

		Enemy();
		void enemy_pattern0(int i);
		void enemy_pattern1(int i);
		void enemy_enter(int i);
		void enemy_act(int i);         //logic to call in main event loop
		void fire();			  
		ALLEGRO_BITMAP *bitmap;
		int flag;			//1 if enemy is active, 0 if not on screen
		int counter;		//time elapsed since enemy spawned
		int hp;
		int hp_max;
		int item;			//what item the enemy drops
		int bullet_time;	//when enemy should start firing

};

void enemies_logic(Enemy enemy[]);