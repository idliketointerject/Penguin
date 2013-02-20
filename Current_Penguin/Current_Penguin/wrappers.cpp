#include "wrappers.h"

// bitmapWrapper functions
bitmapWrapper::bitmapWrapper(char * path)
{
	bitmapPointer = NULL;
	bitmapPointer = al_load_bitmap(path);
}

bool bitmapWrapper::verifyInitialization()
{
	if ( ! bitmapPointer )
	{
		return false;
	}
	return true;
}

ALLEGRO_BITMAP * bitmapWrapper::getBitmapPointer()
{
	return bitmapPointer;
}


bitmapWrapper::~bitmapWrapper()
{
	if ( bitmapPointer )
	{
		al_destroy_bitmap( bitmapPointer );
	}
}

//displayWrapper functions
displayWrapper::displayWrapper(int dWidth, int dHeight)
{
	displayPointer = NULL;
	displayPointer = al_create_display(dWidth, dHeight);
}

bool displayWrapper::verifyInitialization()
{
	if ( ! displayPointer )
	{
		return false;
	}
	return true;
}

ALLEGRO_DISPLAY * displayWrapper::getDisplayPointer()
{
	return displayPointer;
}

displayWrapper::~displayWrapper()
{
	if ( displayPointer )
	{
		al_destroy_display(displayPointer);
	}
}

//timerWrapper functions
timerWrapper::timerWrapper(int fps)
{
	timerPointer = NULL;
	timerPointer = al_create_timer( 1.0 / fps );
}

bool timerWrapper::verifyInitialization()
{
	if ( ! timerPointer )
	{
		return false;
	}
	return true;
}

ALLEGRO_TIMER * timerWrapper::getTimerPointer()
{
	return timerPointer;
}

timerWrapper::~timerWrapper()
{
	if ( timerPointer )
	{
		al_destroy_timer(timerPointer);
	}
}

//eventQueueWrapper functions
eventQueueWrapper::eventQueueWrapper()
{
	eventQueuePointer = NULL;
	eventQueuePointer = al_create_event_queue();
}

bool eventQueueWrapper::verifyInitialization()
{
	if ( ! eventQueuePointer )
	{
		return false;
	}
	return true;
}

ALLEGRO_EVENT_QUEUE * eventQueueWrapper::getEventQueuePointer()
{
	return eventQueuePointer;
}

eventQueueWrapper::~eventQueueWrapper()
{
	if ( eventQueuePointer )
	{
		al_destroy_event_queue(eventQueuePointer);
	}
}

//sampleWrapper functions
sampleWrapper::sampleWrapper(char * path )
{
	samplePointer = NULL;
	samplePointer = al_load_sample(path);
}

bool sampleWrapper::verifyInitialization()
{
	if ( ! samplePointer )
	{
		return false;
	}
	return true;
}

ALLEGRO_SAMPLE * sampleWrapper::getSamplePointer()
{
	return samplePointer;
}

sampleWrapper::~sampleWrapper()
{
	if ( samplePointer )
	{
		al_destroy_sample(samplePointer);
	}
}
