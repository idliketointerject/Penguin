
// Penguin Game

// Imports
#include "wrappers.h"
#include "Globals.h"
#include "Object.h"
#include "initAllegro.h"
#include "InputHandler.h"

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

	/*/ Create Event Queue
	eventQueueWrapper wEventQueue;
	*/
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


	// Game Objects;
	//Penguin penguin;
	object enemies[ NUM_ENEMIES ];

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

			if( state = PLAYING )
			{
				// Update BackGround

				// Update/Move/doAction Penguin

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

				// Draw penguin

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
