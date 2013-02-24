#include "Utility.h"

int randInt(int min, int max)
{
	int range = max - min;
    return rand() % range + min;
}