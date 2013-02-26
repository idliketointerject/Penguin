#include "obstacle.h"
#include "initgame.h"
#include "Globals.h"

#define MAX_ENEMIES 5

class Enemy : public object{
	public:

		Enemy();
		void enemy_pattern0(int i);
		void enemy_pattern1(int i);
		void enemy_pattern2(int i);
		void enemy_pattern3(int i);
		void enemy_enter(int i);		//resets and initializes enemy information to spawn in a new wave
		void enemy_act(int i);         //logic to call in main event loop
		void fire();
		int flagUp(){return flag;};
		void setFlag(int n){flag = n;};
		int getCounter(){return counter;};
		void setCounter(int cnt){counter = cnt;};
	private:
		int flag;			//1 if enemy is active, 0 if not on screen. Only enemies with flag == 1 are drawn by draw_enemies()
		int counter;		//time elapsed since enemy spawned
		int hp;
		int hp_max;
		int item;			//what item the enemy drops
		int bullet_time;	//when enemy should start firing

};

void enemies_logic(Enemy enemy[]);