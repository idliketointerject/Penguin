#include "score.h"


void scorekeeper::printScore(){
	al_draw_textf(getFont(),al_map_rgb(255,255,255),WIDTH - 100, 10, 0, "%i", score);
}