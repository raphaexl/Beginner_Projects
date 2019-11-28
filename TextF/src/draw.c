#include "prototypes.h"

int updateRenderer(Context *C)
   {
   	
   SDL_GetWindowSize(getWindow(),&C->w,&C->h);
     if(SDL_RenderClear(getRenderer()))
     {
     	fprintf(stderr, " Erreur SDL_RenderClear() %s\n", SDL_GetError());
     	return -1;
     }
     if(setWindowColor())return -1;
      C->pos[0].x = C->w/2 - C->pos[0].w/2;
     for (int i = 1; i < C->len; ++i)
     {
        C->pos[i].x = 5;
       
          C->pos[i].y = C->pos[i-1].y + C->pos[i-1].h+0.2 ;
       
     }
    for(int i=0;i<C->len;++i)
   if(drawImage(C->message[i],0,0,C->pos[i])) return -1;
   SDL_RenderPresent(getRenderer());
  return 0;
   }

   int drawImage(SDL_Texture *image, int srcx, int srcy, SDL_Rect dest)
   {
   	  SDL_Rect src = {srcx,srcy,dest.w,dest.h};
   	  if(SDL_RenderCopy(getRenderer(),image,&src,&dest))
   	  {
   	  	fprintf(stderr, "Erreur SDL_RenderCopy() %s\n", SDL_GetError());
   	  	return -1;
   	  }
   	  return 0;
   }

   int setWindowColor(void)
   {
    Uint32 time_one =0, time_now = 0;
    time_now = SDL_GetTicks();
    if(time_now - time_one>3000)
    {
      SDL_Color color = {randomNumber(0,255),randomNumber(0,255),randomNumber(0,255), 255};
      if(SDL_SetRenderDrawColor(getRenderer(),color.r,color.g,color.b,255))
      {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor() %s\n",SDL_GetError() );
        return -1;
      }
      time_one = time_now;
    }
    else
    {
      SDL_Delay(3000-(time_now - time_one));
    }
    return 0;
   }
