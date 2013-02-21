#include "SoundManager.h"

soundManager::soundManager()
{
	al_reserve_samples(NUM_SAMPLES);
}

bool soundManager::setMusic(char * path)
{
	return Music.setSample(path);
}

void soundManager::loopMusic()
{
	al_play_sample(Music.getSamplePointer(),1,0,1,ALLEGRO_PLAYMODE_LOOP, NULL);
}