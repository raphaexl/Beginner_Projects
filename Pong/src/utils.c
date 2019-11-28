#include "prototypes.h"
 int randomNumber(int min, int max)
 {
 	static bool initialized = false;
 	if(!initialized)
 	{
 		srand(time(NULL));
 		initialized = true;
 	}
 	return rand()%(max-min)+min;
 }

 int collision(SDL_Rect ball, SDL_Rect pad)
 {
 	  if(ball.x>pad.x + pad.w||ball.x + ball.w <pad.x)return 0;
 	  if(ball.y>pad.y + pad.h || ball.y + ball.h <pad.y) return 0;
 	  return 1;
 }

  int collisionOne(SDL_Rect pos1,SDL_Rect pos2)
  {
  	 if(pos1.x+pos1.w>=pos2.x && pos1.x<=pos2.x + pos2.w && pos1.y+pos1.h >= pos2.y && pos1.y<=pos2.y + pos2.h) return 1;
  	 return 0;
  }
 Uint32 time_left(Uint32 nextime)
 {
 	Uint32 now = SDL_GetTicks();
 	return (nextime<=now)?0:nextime-now;
 }