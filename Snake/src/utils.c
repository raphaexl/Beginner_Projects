#include "prototypes.h"

int randomNumber(int min, int max)
{
	static bool initialized  = false;
	if(initialized)
	{
	srand(time(NULL));
	initialized = true;
	}

	return rand()%(max-min)+min;
}
