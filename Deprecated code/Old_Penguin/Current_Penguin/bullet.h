#include "obstacle.h"
#include "initgame.h"
#include "math.h" 

#define MAX_BULLETS 30

class Bullet : public obstacle{
	public:

		Bullet();
		ALLEGRO_BITMAP *bitmap;
		//double angleToPenguin(int n, penguin p, Enemy enm[]);
		int flag;
		int counter;
		int color;
		int state;
		int time;
		int fx;
		int num;
		double angle;

};