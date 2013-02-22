
// Penguin Game

// Imports
#include "wrappers.h"
#include "Globals.h"
#include "Object.h"
#include "initAllegro.h"
#include "InputHandler.h"
#include "penguin.h"
#include "backGround.h"
#include "score.h"
#include "screenprinter.h"
#include "SoundManager.h"

#include "draw.h"

int main(int argc, char **argv)
{
	// GAME-LOOP Variables
	bool render = false;
	int state = TITLE;

	// Here is where we Initialize Allegro
	if (!initializeAllegro()) 
		return -1;

	// Create Display
	displayWrapper wDisplay(WIDTH, HEIGHT);
	if (!wDisplay.verifyInitialization()) 
		return -1;

	// Create Input/Event Handler
	inputHandler handler;
	if (!handler.verifyInitialization())
		return -1;

	// Create Timer
	timerWrapper wTimer(FPS);
	if(!wTimer.verifyInitialization())
		return -1;

	// Register Event Sources
	handler.registerSource(al_get_timer_event_source(wTimer.getTimerPointer()));

	// Background Object
	backGround bg("resources/images/background.png");
	if (!bg.verifyBitmap())
		return -8;
	bg.setSpeedX(3);
	bg.setDirX(-1);

	// Menu Object
	backGround startMenu("resources/images/menu.png");
	if(!startMenu.verifyBitmap())
		return -2;
	
	// SoundManager
	soundManager sManager;
	if( !sManager.setBGMusic("resources/audio/bgm.wav"))
		return -3;
	if( !sManager.setTitleMusic("resources/audio/menu_bgm.wav"))
		return -3;

	// Game Objects;
	//Penguin penguin;
	penguin pengii("resources/images/penguin.png");
	if(!pengii.verifyBitmap())
		return -4;
	pengii.setSpeedX( 10.0 );
	pengii.setSpeedY( 10.0 );

	//object enemies[ NUM_ENEMIES ];
	//Enemy enm[MAX_ENEMIES];

	// ScoreKeeper
	scorekeeper totalScore;
	totalScore.setFont( al_load_font("Escape.ttf",24,0) );
	if( !totalScore.getFont())
		return -5;

	// Screen Printer
	screenprinter titleHelp("Escape.ttf");
	titleHelp.setTextSize(20);
	titleHelp.setXPos(WIDTH/2 - 100);

	// Play Music
	//sManager.loopMusic();
	//menuMusic.loopMusic();

	// Starting Timer: Put Nothing between here and start of game loop!
	al_start_timer(wTimer.getTimerPointer());

	while(!handler.getDone())
	{
		handler.waitForEvent();
		if (handler.handleEvent())
		{
			if (handler.getKey(KEY_SPACE) && ( state == TITLE || state == ENDGAME ) )
			{
				// If spacebar is pressed in title screen/endgame screen the game will revert to playing
				// This needs to be changed eventually to reset the game before resuming it
				state = PLAYING;
				handler.changeKey(KEY_SPACE);
			}
		}
		else if(handler.doUpdate()) // UPDATE GAME
		{
			render = true;
			sManager.update(state);

			if( state == PLAYING )
			{
				
				// Update BackGround
				bg.update();
				totalScore.incrementscore();
				// Update/Move/doAction Penguin
				pengii.move(handler.getKeysArray());

				// here we update live objects
				//enemies_logic(enm);
/*				for( int i = 0; i < NUM_ENEMIES; i++ )
				{
					if (enemies[i].isAlive())
					{
						enemies[i].update();
					}
				}*/

				// Check/Handle Collisions
			}
		}

		if (render && handler.isEmpty())
		{
			render = false;
			if (state == TITLE)
			{
				// Display TitleMenu!
				startMenu.drawScaled();
				titleHelp.printText("Press the spacebar to play!~");

			}
			else if(state == ENDGAME)
			{
				// Display Endgame Menu
			}
			else if(state == PLAYING)
			{
				// Draw Background
				bg.drawYScaled();
				totalScore.printScore();
				// Draw penguin
				pengii.draw();
				// Draw Enemies
				//draw_enemies(enm);
/*				for ( int i=0; i < NUM_ENEMIES; i++)
				{
					if( enemies[i].isAlive())
					{
						enemies[i].draw();
					}
				}*/
			}

			// Flip buffers
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}

	}

	return 0;

}
