#include "wrappers.h"

// bitmapWrapper functions
bitmapWrapper::bitmapWrapper()
{
	bitmapPointer = NULL;
	locked = false;
}
bitmapWrapper::bitmapWrapper(char * path)
{
	locked = false;
	bitmapPointer = NULL;
	setBitmap(path);
}

bool bitmapWrapper::setBitmap(char * path)
{
	if (locked)
	{
		return false;
	}
	bitmapPointer = al_load_bitmap(path);
	locked = true;
	return verifyInitialization();
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
timerWrapper::timerWrapper()
{
	locked = false;
	timerPointer = NULL;
}

timerWrapper::timerWrapper(int fps)
{
	locked = false;
	timerPointer = NULL;
	setTimer(fps);
}

bool timerWrapper::setTimer(int fps)
{
	if (locked)
	{
		return false;
	}
	timerPointer = al_create_timer( 1.0 / fps);
	locked = true;
	return verifyInitialization();
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
sampleWrapper::sampleWrapper()
{
	locked = false;
	samplePointer = NULL;
}

sampleWrapper::sampleWrapper(char * path )
{
	locked = false;
	samplePointer = NULL;
	setSample(path);
}

bool sampleWrapper::setSample( char * path )
{
	if (locked)
	{
		return false;
	}
	samplePointer = al_load_sample(path);
	locked = true;
	return verifyInitialization();
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
