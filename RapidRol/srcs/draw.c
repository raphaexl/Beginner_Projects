#include "prototypes.h"

int y=0;
int updateRenderer(Context *C,Balle *balle)
 {
 	 if(SDL_RenderClear(getRenderer()))
 	 {
 	 	fprintf(stderr, " Erreur SDL_RenderClear() %s\n", SDL_GetError());
 	 	return -1;
 	 }
 	 if(SDL_SetRenderDrawColor(getRenderer(),125,89,201,254))
 	 {
 	 	fprintf(stderr, "Erreur SDL_SetRenderDrawColor() %s\n", SDL_GetError());
 	 	return -1;
 	 }
 	 for(int i=0;i<5;++i)
   if(drawImage(C->pads[i],0,0,C->pos[i])) return -1;
    if(drawImage(balle->img,0,0,balle->pos)) return -1;
    
  for (int i = 0; i < 5; ++i)
    {
    	C->pos[i].y -=C->speed;
    	if(C->pos[i].y+C->pos[i].h<=0)
    		C->pos[i].y = SCREEN_HEIGHT + C->pos[i].y;
    }
    SDL_RenderPresent(getRenderer());
    return 0;
 }

 int drawImage(SDL_Texture *image, int x, int y,SDL_Rect pos)
 {
 	SDL_Rect src = {x,y,pos.w,pos.h};
 	if(SDL_RenderCopy(getRenderer(),image,&src,&pos))
 	{
 		fprintf(stderr, "Erreur SDL_RenderCopy() %s\n", SDL_GetError());
 		return -1;
 	}
 	return 0;
 }

 

 
