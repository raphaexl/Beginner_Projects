  #include "prototypes.h"
int updateRenderer(Context *C,Balle *balle,Paddle *paddle1,Paddle *paddle2)
{
	SDL_GetWindowSize(getWindow(),&C->w,&C->h);
	 C->pos[1].x = C->w/2 - 5;
    C->pos[2].x = C->w -15;
     for(int i=0;i<3;++i)
    C->pos[i].h = C->h- 5;
    C->pos[4].y = C->h - 15; 
     for(int i=3;i<5;++i)
    C->pos[i].w = C->w - 5;
    paddle2->pos.x = C->w - 70;
	if(SDL_RenderClear(getRenderer()))
	{
		fprintf(stderr, "Erreur SDL_RenderClear() %s\n",SDL_GetError() );
		return -1;
	}
	for (int i = 0; i < 5; ++i)
	{
	if(draw_image(C->cadre[i],0,0,C->pos[i])) return -1;
	}
	if(draw_image(paddle1->img,0,0,paddle1->pos)) return -1;
	if(draw_image(paddle2->img,0,0,paddle2->pos)) return -1;
	if(draw_image(balle->img,0,0,balle->pos)) return -1;
	SDL_RenderPresent(getRenderer());
	return 0;
}

SDL_Texture *loadImage(char *path)
{
	 SDL_Surface *surf = NULL;
	 surf = IMG_Load(path);
	 if(!surf)
	 {
	 	fprintf(stderr, "Erreur SDL_LoadImage() %s\n",SDL_GetError() );
	 	return NULL;
	 }
 if(SDL_SetColorKey(surf,SDL_TRUE,SDL_MapRGB(surf->format,255,255,255)))
 {
 	fprintf(stderr, " Erreur SDL_SetColorKey() %s\n",SDL_GetError());
 	return NULL;
 }
 SDL_Texture *image = SDL_CreateTextureFromSurface(getRenderer(),surf);
 if(!image)
 {
 	fprintf(stderr, "Erreur SDL_GetError() %s\n", SDL_GetError());
 	return NULL;
 }

 SDL_FreeSurface(surf),surf = NULL;

 return image;

}

int draw_image(SDL_Texture *image,int x,int y,SDL_Rect pos)
{
	SDL_Rect src = {x,y,pos.w,pos.h};
	if(SDL_RenderCopy(getRenderer(),image,&src,&pos))
	{
		fprintf(stderr, "Erreur SDL_RenderCopy() %s\n",SDL_GetError() );
		return -1;
	}
	return 0;
}
