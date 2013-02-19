#include "InputHandler.h"

inputHandler::inputHandler()
{
	numKeys = NUM_KEYS;
	for( int i = 0; i < numKeys; i++ )
	{
		keys[i] = false;
	}
	registerSource(al_get_keyboard_event_source());
	done = false;
}

bool inputHandler::verifyInitialization()
{
	if (! wEventQueue.verifyInitialization())
		return false;
	return true;
}

void inputHandler::registerSource(ALLEGRO_EVENT_SOURCE *source)
{
	al_register_event_source(wEventQueue.getEventQueuePointer(), source);
}

void inputHandler::waitForEvent()
{
	al_wait_for_event(wEventQueue.getEventQueuePointer(), &ev);
}

bool inputHandler::handleEvent()
{

	if(ev.type == ALLEGRO_EVENT_KEY_DOWN) 
	{
		switch(ev.keyboard.keycode) 
		{
		case ALLEGRO_KEY_UP:
			keys[KEY_UP] = true;
			break;
		case ALLEGRO_KEY_DOWN:
			keys[KEY_DOWN] = true;
			break;
		case ALLEGRO_KEY_LEFT: 
			keys[KEY_LEFT] = true;
			break;
		case ALLEGRO_KEY_RIGHT:
			keys[KEY_RIGHT] = true;
			break;
		case ALLEGRO_KEY_SPACE:
			keys[KEY_SPACE] = true;
			break;
		case ALLEGRO_KEY_ESCAPE:
			done = true;
			break;
		}
		return true;
	}
	else if(ev.type == ALLEGRO_EVENT_KEY_UP) 
	{
		switch(ev.keyboard.keycode) 
		{
		case ALLEGRO_KEY_UP:
			keys[KEY_UP] = false;
			break;
		case ALLEGRO_KEY_DOWN:
			keys[KEY_DOWN] = false;
			break;
		case ALLEGRO_KEY_LEFT: 
			keys[KEY_LEFT] = false;
			break;
		case ALLEGRO_KEY_RIGHT:
			keys[KEY_RIGHT] = false;
			break;
		case ALLEGRO_KEY_SPACE:
			keys[KEY_SPACE] = false;
			break;
		}
		return true;
	}
	return false;
}

bool inputHandler::doUpdate()
{
	if( ev.type == ALLEGRO_EVENT_TIMER )
		return true;
	return false;
}

bool inputHandler::isEmpty()
{
	return al_is_event_queue_empty(wEventQueue.getEventQueuePointer());
}