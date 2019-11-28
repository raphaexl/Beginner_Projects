
#include "defs.h"

int randomNumber(int min, int max)
{
	static bool initialized = false;
	if(!initialized)
	{
	srand(time(NULL));
	initialized = true;
	}

	return rand()%(max - min)+min;
}

int negatModulo(int x, int max)
{
	 if(x>0)
	 	return x%max;
	 else
	 	return (x%max) + max;
}
int collision(SDL_Rect pos1,SDL_Rect pos2)
{
	if((pos1.x+pos1.w <=pos2.x)||(pos1.x>=pos2.x+pos2.w)) return 0;

	if((pos1.y+pos1.h<=pos2.y)||(pos1.y>=pos2.y + pos2.h)) return 0;
	return 1;
}