#ifndef STARTGAME_H
#define STARTGAME_H

#include <stdio.h>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "allegro5/allegro_image.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
//#include <allegro5/display.h>
//#include "menu.h"
#include "score.h"

//al_create_display(w, h);
const int SCREEN_W = 640;//640
const int SCREEN_H = 480;//480

/*
class startgame{
	public:
	int initgame();

};
*/
int initgame();

#endif