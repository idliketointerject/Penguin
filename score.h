#ifndef SCORE_H
#define SCORE_H

class scorekeeper{
public:

	scorekeeper(){
		score = 0;
	}
	void incrementscore(){
		score++;
	}
	int getscore(){
		return score;
	}
	void setscore(int total){
		score = total;
	}
	int score;
private:
	//int score;
};

#endif
