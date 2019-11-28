
#include "prototypes.h"

SDL_Texture *loadImage(char *path)
{
	 SDL_Surface *surf = NULL;
	 SDL_Texture *image  = NULL;
	 surf = IMG_Load(path);
	 if(!surf)
	 {
	  fprintf(stderr, " Erreur IMG_Load() %s\n",IMG_GetError() );
	  return NULL;
	 }
	 if(SDL_SetColorKey(surf,SDL_TRUE,SDL_MapRGB(surf->format,255,255,255)))
	 {
	 	fprintf(stderr, "Erreur SDL_SetColorKey()%s\n",SDL_GetError());
	 	return NULL;
	 }

	 image = SDL_CreateTextureFromSurface(getRenderer(),surf);
	 if(!image)
	 {
	 	fprintf(stderr, "Erreur SDL_CreateTextureFromSurface() %s\n", SDL_GetError());
	 	return NULL;
	 }
	 return image;
}

SDL_Texture *loadImage2(char *path)
{
	 SDL_Surface *surf = NULL;
	 SDL_Texture *image  = NULL;
	 surf = IMG_Load(path);
	 if(!surf)
	 {
	  fprintf(stderr, " Erreur IMG_Load() %s\n",IMG_GetError() );
	  return NULL;
	 }
	 if(SDL_SetColorKey(surf,SDL_TRUE,SDL_MapRGB(surf->format,0,0,0)))
	 {
	 	fprintf(stderr, "Erreur SDL_SetColorKey()%s\n",SDL_GetError());
	 	return NULL;
	 }

	 image = SDL_CreateTextureFromSurface(getRenderer(),surf);
	 if(!image)
	 {
	 	fprintf(stderr, "Erreur SDL_CreateTextureFromSurface() %s\n", SDL_GetError());
	 	return NULL;
	 }
	 return image;
}

int updateRenderer(Context *C)
{
	 if(SDL_RenderClear(getRenderer()))
	 {
	 	fprintf(stderr, "Erreur SDL_RenderClear() %s\n",SDL_GetError() );
	 	return -1;
	 }
	 if(SDL_SetRenderDrawColor(getRenderer(),124,104,23,255))
	 {
	 	fprintf(stderr, "Erreur SDL_SetRenderDrawColor() %s\n",SDL_GetError());
	 	return -1;
	 }
         for (int i = 0; i < 20; ++i)
         {
         	if(C->balle[i].pos.y<SCREEN_HEIGHT-C->balle[i].pos.h)
         	{
         	C->balle[i].pos.y += C->balle[i].vy;
         	C->balle[i].vy += C->balle[i].gravite;	
         	}
            else 
            {

            	C->balle[i].vy *=-C->balle[i].elasticite; 
                C->balle[i].pos.y += 2*C->balle[i].vy;
             if(fabs(C->balle[i].vy) <0.1)
            	 	C->balle[i].vy = 0;
            }
         	
         }
         for (int i = 0; i < 20; ++i)
         {
         	if(drawImage(C->balle[i].img,0,0,C->balle[i].pos)) return -1;
         }
	 SDL_RenderPresent(getRenderer());
	 return 0;
}



int drawImage(SDL_Texture *image,int x, int y, SDL_Rect pos)
{
	SDL_Rect src = {x,y,pos.w,pos.h};
	if(SDL_RenderCopy(getRenderer(),image,&src,&pos))
	{
		fprintf(stderr, "Erreur SDL_RenderCopy() %s\n", SDL_GetError());
		return -1;
	}
	return 0;
}