#pragma once

#include "initAllegro.h"
#include "wrappers.h"


class soundManager
{
public:
	soundManager();
	bool setBGMusic(char * path);
	bool setTitleMusic(char * path);
	void loopBGMusic();
	void loopTitleMusic();
	void update(int state);

private:
	int currentState;
	sampleWrapper BGMusic;
	sampleWrapper TitleMusic;
};