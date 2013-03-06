#ifndef SCORE_H
#define SCORE_H
#include "Object.h"
#include <allegro5/allegro_font.h>
#include <fstream>
#include <iostream>
#include <string>

class scorekeeper{
public:

	scorekeeper(){
		font24 = NULL;
		//font24 = al_load_font("Escape.ttf",24,0);
		score = 0;
	}
	void setFont(ALLEGRO_FONT * font)
	{
		font24 = font;
	}
	void incrementscore(){
		++score;
	}
	int getscore(){
		return score;
	}
	void setscore(int total){
		score = total;
	}
	void printScore();
	ALLEGRO_FONT * getFont(){
		return font24;
	}

	void printHighScores();

	void saveScore();

	int* loadHighScores();
	int lowestScore(int* scores, int size);
	void sortScores(int* highscores, int size);

private:
	int score;
	ALLEGRO_FONT* font24;
};

#endif
