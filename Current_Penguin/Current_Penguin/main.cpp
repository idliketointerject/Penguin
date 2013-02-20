
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

int main(int argc, char **argv)
{
	// GAME-LOOP Variables
	bool render = false;
	int state = PLAYING;

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
	bitmapWrapper backImage("resources/images/background.png");
	if (!backImage.verifyInitialization())
		return -1;

	backGround bg;
	bg.setImage(backImage.getBitmapPointer());
	//bg.playMusic("resources/audio/bgm.wav");

	backGround bg2;
	bg2.setImage(backImage.getBitmapPointer());
	bg2.setX(backImage.getBitmapWidth());
	
	// Game Objects;
	//Penguin penguin;
	bitmapWrapper penguinImage("resources/images/penguin.png");

	if(!penguinImage.verifyInitialization())
		return -1;

	penguin pengii;
	pengii.setImage(penguinImage.getBitmapPointer());
	pengii.setSpeedX( 10.0 );
	pengii.setSpeedY( 10.0 );

	object enemies[ NUM_ENEMIES ];

	// ScoreKeeper
	scorekeeper totalScore;
	totalScore.setFont( al_load_font("Escape.ttf",24,0) );
	if( !totalScore.getFont())
		return -1;

	al_start_timer(wTimer.getTimerPointer());
	bg.playMusic("resources/audio/bgm.wav");//why doesn't this work???

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

			if( state = PLAYING )
			{

				// Update BackGround
				bg.scrollBackGround();
				bg2.scrollBackGround();
				totalScore.incrementscore();
				// Update/Move/doAction Penguin
				pengii.move(handler.getKeysArray());

				// here we update live objects
				for( int i = 0; i < NUM_ENEMIES; i++ )
				{
					if (enemies[i].isAlive())
					{
						enemies[i].update();
					}
				}

				// Check/Handle Collisions
			}
		}

		if (render && handler.isEmpty())
		{
			render = false;
			if (state == TITLE)
			{
				// Display TitleMenu!
			}
			else if(state == ENDGAME)
			{
				// Display Endgame Menu
			}
			else if(state == PLAYING)
			{
				// Draw Background
				bg.draw();
				bg2.draw();
				totalScore.printScore();
				// Draw penguin
				pengii.draw();
				// Draw Enemies
				for ( int i=0; i < NUM_ENEMIES; i++)
				{
					if( enemies[i].isAlive())
					{
						enemies[i].draw();
					}
				}
			}

			// Flip buffers
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}

	}

	return 0;

}
