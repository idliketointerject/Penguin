#include "score.h"
using namespace std;

void scorekeeper::printScore(){
	al_draw_textf(getFont(),al_map_rgb(255,255,255),WIDTH - 100, 10, 0, "%i", score);
}

void scorekeeper::saveScore(){
	ofstream scorefile ("scores.txt", ios::app);
	if (scorefile.is_open())
	{
		scorefile << score << endl;
		scorefile.close();
	}
}

int* scorekeeper::loadHighScores(){
	ifstream scorefile ("scores.txt");
	string line;
	int* highscores = new int[5];

	for(int i = 0; i < 5; i++)
	{
		highscores[i] = 0;
	}

	if (scorefile.is_open())
	{
		while (scorefile.good())
		{
			getline(scorefile,line);

			char * cstr = new char [line.length()+1];
			std::strcpy (cstr, line.c_str());

			int temp = atoi(cstr);

			delete [] cstr;
					
			if(temp > highscores[lowestScore(highscores, 5)])
			{
				highscores[lowestScore(highscores,5)] = temp;
			}

		}
		scorefile.close();
	}
	sortScores(highscores, 5);

	return highscores;
}

int scorekeeper::lowestScore(int* scores, int size){

	int lowest = scores[0];
	int index = 0;

	for (int i = 0; i < size; i++)
	{
		if(scores[i] < lowest)
		{
			lowest = scores[i];
			index = i;
		}
	}

	return index;
}

void scorekeeper::sortScores(int* highscores, int size){

	for(int i = 0; i < size; i++)
	{
		int temp = highscores[lowestScore(highscores,size-i)];
		highscores[lowestScore(highscores,size-i)] = highscores[size-1-i];
		highscores[size-1-i] = temp;
	}

}


void scorekeeper::printHighScores() {
	ALLEGRO_FONT* font = al_load_font("comic_zine_ot.otf",48,0);
	

	int* highscores = loadHighScores();
	int yourscore = getscore();

	bool found = false;

	if(yourscore > highscores[0])
	{
		al_draw_textf(font,al_map_rgb(0,0,195),WIDTH/2 - 50, HEIGHT/2 - 125, 0, "NEW RECORD! %i", yourscore);
	}
	else
	{
		for(int i = 1; i < 5; i++)
		{
			if(yourscore > highscores[i])
			{
				al_draw_textf(font,al_map_rgb(0,0,195),WIDTH/2 - 50, HEIGHT/2 - 125, 0, "HIGH SCORE! %i", yourscore);
				found = true;
				break;
			}
		}
	}

	if(!found)
	{
		al_draw_textf(font,al_map_rgb(0,0,195),WIDTH/2 - 50, HEIGHT/2 - 125, 0, "Your score: %i", yourscore);
	}

	al_draw_textf(font,al_map_rgb(0,0,195),WIDTH/2 - 50, HEIGHT/2 - 50, 0, "%s", "Highscores!!");
	al_draw_textf(font,al_map_rgb(0,0,195),WIDTH/2 - 50, HEIGHT/2, 0, "1) %i", highscores[0]);
	al_draw_textf(font,al_map_rgb(0,0,195),WIDTH/2 - 50, HEIGHT/2 + 50, 0, "2) %i", highscores[1]);
	al_draw_textf(font,al_map_rgb(0,0,195),WIDTH/2 - 50, HEIGHT/2 + 100, 0, "3) %i", highscores[2]);
	al_draw_textf(font,al_map_rgb(0,0,195),WIDTH/2 - 50, HEIGHT/2 + 150, 0, "4) %i", highscores[3]);
	al_draw_textf(font,al_map_rgb(0,0,195),WIDTH/2 - 50, HEIGHT/2 + 200, 0, "5) %i", highscores[4]);
}