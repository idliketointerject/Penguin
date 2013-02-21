#pragma once

#include "initAllegro.h"
#include "wrappers.h"


class soundManager
{
public:
	soundManager();
	bool setMusic(char * path);
	void loopMusic();


private:
	sampleWrapper Music;
};