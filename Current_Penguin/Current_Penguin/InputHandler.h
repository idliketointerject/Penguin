// Class to handle Events
#pragma once
#include "initAllegro.h"
#include "wrappers.h"

#define NUM_KEYS 5

class inputHandler
{
public:
	inputHandler();
	void registerSource(ALLEGRO_EVENT_SOURCE *source);
	void waitForEvent();
	bool verifyInitialization();
	bool handleEvent();
	bool doUpdate();
	bool isEmpty();
	// Getters/Setters
	bool * getKeysArray() {return keys;}
	int getKeysArraySize() {return numKeys;}
	bool getDone() {return done;}
	bool getKey(int pos) {return keys[pos];}
	ALLEGRO_EVENT getEvent() {return ev;}
	void changeKey(int pos) {keys[pos] = !keys[pos];}
	void setKey(int pos, bool value) {keys[pos] = value;}
private:
	eventQueueWrapper wEventQueue;
	bool keys[NUM_KEYS];
	int numKeys;
	ALLEGRO_EVENT ev;
	bool done;
};