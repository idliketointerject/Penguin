#include "initAllegro.h"

bool initializeAllegro()
{
	
	// Install Addons
	if(!al_init()) 
	{
		fprintf(stderr, "failed to initialize allegro!\n");
		return false;
	}
 
	if(!al_init_image_addon()) 
	{
		fprintf(stderr, "failed to initialize al_init_image_addon!\n");
		return false;
	}

	if(!al_install_keyboard()) 
	{
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return false;
	}
 
	if(!al_install_audio())
	{
		fprintf(stderr, "failed to initialize audio!\n");
		return false;
	}
 
	if(!al_init_acodec_addon())
	{
		fprintf(stderr, "failed to initialize audio codecs!\n");
		return false;
	}
 
	if (!al_reserve_samples(NUM_SAMPLES))
	{
		fprintf(stderr, "failed to reserve samples!\n");
		return false;
	}
	// All Addons Successfully Installed!
	return true;
}