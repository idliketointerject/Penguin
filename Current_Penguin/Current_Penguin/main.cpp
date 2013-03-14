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
#include "ObstacleHandler.h"
#include "powerUpHandler.h"
#include "enemy.h"

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
	bg.setSpeedX(5);
	bg.setDirX(-1);

	// Menu Object
	backGround startMenu("resources/images/menu.png");
	if(!startMenu.verifyBitmap())
		return -2;

	backGround howtoPlay("resources/images/howtoplay.png");
	if(!startMenu.verifyBitmap())
		return -2;
	
	//endgame object
	backGround endMenu("resources/images/end.png");
	if(!endMenu.verifyBitmap())
		return -2;

	// SoundManager
	soundManager sManager;
	if( !sManager.setBGMusic("resources/audio/aqua_star.wav"))
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
	pengii.setLives(3);
	pengii.setCollidable(true);
	pengii.setAlive(true);

	Enemy enm[MAX_ENEMIES];
	for (int i=0; i < MAX_ENEMIES; i++)
	{
		if(!enm[i].verifyBitmap())
			return -4;
	}

	// Obstacles
	obstacleHandler obstacHandler("resources/images/mine.png");
	if(!obstacHandler.verifyBitmaps())
		return -9;

	// Health PowerUps
	powerUpHandler healthPower("resources/images/health.png");
	if(!healthPower.verifyBitmaps())
		return -9;

	powerUpHandler speedPower("resources/images/speed.png");
	if(!speedPower.verifyBitmaps())
		return -9;

	// ScoreKeeper
	scorekeeper totalScore;
	//totalScore.setFont( al_load_font("Escape.ttf",24,0) );
	if( !totalScore.getFont())
		return -5;

	// Screen Printer
	screenprinter titleHelp("Escape.ttf");
	titleHelp.setTextSize(20);
	titleHelp.setXPos(WIDTH/2 - 100);

	// Starting Timer: Put Nothing between here and start of game loop!
	al_start_timer(wTimer.getTimerPointer());

	while(!handler.getDone())
	{
		handler.waitForEvent();
		if (handler.handleEvent())
		{
			if (handler.getKey(KEY_SPACE) && ( state == TITLE ) )
			{
				totalScore.setscore(0);
				pengii.reset();
				obstacHandler.reset();
				healthPower.reset();
				speedPower.reset();				// If spacebar is pressed in title screen/endgame screen the game will revert to playing
				// This needs to be changed eventually to reset the game before resuming it
				state = PLAYING;
				handler.changeKey(KEY_SPACE);
			}
			else if (handler.getKey(KEY_SPACE) && (state == HELP))
			{
				state = TITLE;
				handler.changeKey(KEY_SPACE);
			}
			else if(handler.getKey(KEY_ENTER) && (state == ENDGAME))
			{
				totalScore.setscore(0);
				pengii.reset();
				obstacHandler.reset();
				healthPower.reset();
				speedPower.reset();				// If spacebar is pressed in title screen/endgame screen the game will revert to playing
				// This needs to be changed eventually to reset the game before resuming it
				state = PLAYING;
				handler.changeKey(KEY_ENTER);
			}
			else if(handler.getKey(KEY_ENTER) && (state == TITLE))
			{
				state = HELP;
				handler.changeKey(KEY_ENTER);
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
				
				// Check/Handle Object Collisions
				obstacHandler.checkCollision(pengii);
				for (int i=0; i<MAX_ENEMIES; i++)
					enm[i].checkCollision(pengii);

				//check powerup collisions
				healthPower.checkHealthCollision(pengii);
				speedPower.checkSpeedCollision(pengii);

				//bullet collisions check
				obstacHandler.checkCollision(pengii.getBulletArray());
				healthPower.checkCollision(pengii.getBulletArray());
				speedPower.checkCollision(pengii.getBulletArray());
				for (int i=0; i<MAX_ENEMIES; i++)
					enm[i].checkCollision(pengii.getBulletArray());

				// Verify that penguin still has remaining lives
				if (pengii.getLives() <= 0 )
				{
					totalScore.saveScore();
					state = ENDGAME;
				}
				
				// Update/Move/doAction Penguin
				pengii.move(handler.getKeysArray());
				if(handler.getKey(KEY_SPACE))
					handler.setKey(KEY_SPACE, false);

				// here we update/spawn obstacles
				obstacHandler.update();
				enemies_logic(enm, pengii);
				healthPower.update();
				speedPower.update();

				//update new obstacle spawnconstant
				if(totalScore.getscore() % 10 == 0)
				{
					obstacHandler.updateSpawn();
				}
			}
		}


		if (render && handler.isEmpty())
		{
			render = false;
			if (state == TITLE)
			{
				// Display TitleMenu!
				startMenu.drawScaled();

			}
			else if(state == HELP)
			{
				howtoPlay.drawScaled();
			}
			else if(state == ENDGAME)
			{
				// Display Endgame Menu
				endMenu.drawScaled();
				totalScore.printHighScores();
			}
			else if(state == PLAYING)
			{
				// Draw Background
				bg.drawYScaled();
				totalScore.printScore();
				// Draw penguin
				pengii.draw();
				// Draw Obstacles
				obstacHandler.draw();
				healthPower.draw();
				speedPower.draw();
				// Draw Enemies
				for (int i=0; i<MAX_ENEMIES; i++)
					enm[i].draw();
			}

			// Flip buffers
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}

	}

	return 0;

}
