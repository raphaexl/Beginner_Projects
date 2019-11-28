#include "prototypes.h"

int randomNumber(int min, int max)
{
  static	bool initialized = false;
  if(!initialized)
  {
  srand(time(NULL));
  initialized = true;
  
  }
 return rand()%(max-min)+min;
}


int collision(SDL_Rect pos1,SDL_Rect pos2)
{
	if(pos1.x + pos1.w>=pos2.x && pos1.x<=pos2.x +pos2.w && pos1.y + pos1.h>=pos2.y && pos1.y<=pos2.y+ pos2.h)return -1;
	return 0;
}

int negatModulo(int x,int mod)
{
	if(x>=0)
		return x%mod;
	else
		return (x%mod)+mod;
}