#include "SoundManager.h"

soundManager::soundManager()
{
	currentState = -1;
	al_reserve_samples(NUM_SAMPLES);
}

bool soundManager::setBGMusic(char * path)
{
	return BGMusic.setSample(path);
}

bool soundManager::setTitleMusic(char * path)
{
	return TitleMusic.setSample(path);
}

void soundManager::loopBGMusic()
{
	al_play_sample(BGMusic.getSamplePointer(),1,0,1,ALLEGRO_PLAYMODE_LOOP, NULL);
}

void soundManager::loopTitleMusic()
{
	al_play_sample(TitleMusic.getSamplePointer(),1,0,1,ALLEGRO_PLAYMODE_LOOP, NULL);
}

void soundManager::update(int state)
{
	if ( currentState == -1 )
	{
		loopTitleMusic();
		currentState = TITLE;
	}
	else if ( state != currentState )
	{
		al_stop_samples();
		currentState = state;
		if ( state == TITLE )
		{
			loopTitleMusic();
		}
		else if ( state == PLAYING )
		{
			loopBGMusic();
		}
		else if ( state = ENDGAME )
		{
			//play endgame music
		}
	}
}