#include "Utility.h"

int randInt(int min, int max)
{
	int range = max - min;
    return rand() % range + min;
}

double randAng(double ang)
{
    return ( -ang + ang*2 * randInt(0, 10000)/10000.0 );
}