#include "prototypes.h"

int draw(Context *C,Balle *balle,Paddle *paddle)
{ 
	 if(SDL_RenderClear(getRenderer()))
	 {
	 	fprintf(stderr, "Erreur SDL_ClearRenderer() %s\n", SDL_GetError());
	 	return -1;
	 }
       

	  SDL_GetWindowSize(getWindow(),&C->w,&C->h);
	  C->cadPos[1].h = C->h -16;
	  C->cadPos[0].h = C->h -16;
	  C->cadPos[1].x = C->w - C->cadPos[1].w;
	  C->cadPos[3].y = C->h - C->cadPos[3].h;
	  C->cadPos[2].w = C->w;
	  C->cadPos[3].w = C->w;
      for (int i = 0; i < 4; ++i)
      {
      if(drawImage(C->cadre[i],0,0,C->cadPos[i])) return -1;
      }
     
     if(drawImage(balle->img,0,0,balle->pos))return -1;
     if(drawImage(paddle->img,0,0,paddle->pos)) return -1;
      updateContext(C);
      SDL_Delay(1);
	 SDL_RenderPresent(getRenderer());
	 return 0;
}

int drawImage(SDL_Texture *image,int x, int y, SDL_Rect pos)
{
	SDL_Rect src = {x,y,pos.w,pos.h};
	if(SDL_RenderCopy(getRenderer(),image,&src,&pos))
	{
		fprintf(stderr, "Erreur SDL_RenderCopy() %s\n",SDL_GetError() );
		return -1;
	}
	return 0;
}

SDL_Texture *loadImage(char *path,int R, int G,int B)

 {
 	SDL_Surface *temp = NULL;
 	temp = IMG_Load(path);
 	if(!temp)
 	{
 		fprintf(stderr, "Erreur IMG_Load() %s\n", IMG_GetError());
 		return NULL;
 	}
 	if(SDL_SetColorKey(temp,SDL_TRUE,SDL_MapRGB(temp->format,R,G,B)))
 	{
 		fprintf(stderr, "Erreur SDL_SetColorKey() %s\n",SDL_GetError() );
 		return NULL;
 	}
 	SDL_Texture *image = SDL_CreateTextureFromSurface(getRenderer(),temp);
 	if(!image)
 	{
 		fprintf(stderr, "Erreur SDL_CreateTextureFromSurface() %s\n", SDL_GetError());
 		return NULL;
 	}
 	SDL_FreeSurface(temp),temp = NULL;
 	return image;
 }

int  updateContext(Context *C)
 {
   
 	C->pos.w =  64;
 	C->pos.h = 24;
 	

 	 for (int i = 0; i < C->h/100; ++i)
 	 {
 	 	C->pos.y = i*24.1;
 	 	for(int j=0;j< C->w/64;++j)
 	 	{
 	 		C->pos.x = 16+ j*64;
 	 		if(C->grille[i][j]==1)
 	 		{
 	 			if(drawImage(C->img,0,0,C->pos)) return -1;
 	 		}
 	 		else;
 	 	}
 	 }
 	 return 0;
 }

 int SDL_SetWindowColor(SDL_Color color)
 {
    
	 if(SDL_RenderClear(getRenderer()))
	 {
	 	fprintf(stderr, "Erreur SDL_ClearRenderer() %s\n", SDL_GetError());
	 	return -1;
	 }
       
	 if(SDL_SetRenderDrawColor(getRenderer(),color.r,color.g,color.b,color.a))
	 {
	 	fprintf(stderr, "Erreur SDL_SetRenderDrawColor() %s\n", SDL_GetError());
	 	return -1;
	 }
	 return 0;
 }

 void delay(unsigned int framLimits)
 {
 	unsigned int ticks = SDL_GetTicks()  +16;
 	if(framLimits<ticks)
 		return;
 	if(framLimits>ticks+16)
 		SDL_Delay(16);
 	else
 		SDL_Delay(framLimits-ticks);
 }
