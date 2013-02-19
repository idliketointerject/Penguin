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
private:
	int score;
};