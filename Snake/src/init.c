#include "prototypes.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

  SDL_Renderer *getRenderer(void)
{
	return renderer;
}

int init(char title[])
{
	 if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO))
	 {
	 	fprintf(stderr, " Erreur SDL_Init() %s\n",SDL_GetError() );
	 	return -1;
	 }
	 window = SDL_CreateWindow(title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);
	 if(!window)
	 {
	 	fprintf(stderr, "Erreur SDL_CreateWindow() %s\n",SDL_GetError() );
	 	return -1;
	 }
	 renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	 if(!renderer)
	 {
	 	fprintf(stderr, " Erreur SDL_CreateRenderer() %s\n",SDL_GetError() );
	 	return -1;
	 }
	 if(Mix_Init(MIX_INIT_MP3))
	 {
	 	fprintf(stderr, "Erreur Mix_Init() %s\n", Mix_GetError());
	 	return -1;
	 }
	 if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048))
	 {
	 	fprintf(stderr, " Erreur Mix_OpenAudio() %s\n",Mix_GetError() );
	 	return -1;
	 }

	 Mix_AllocateChannels(32);
	 if(!IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG))
	 {
	 	fprintf(stderr, " Erreur IMG_Init() %s\n",IMG_GetError() );
	 	return -1;
	 }
	 if(TTF_Init())
	 {
	 	fprintf(stderr, " Erreur TTF_Init() %s\n", TTF_GetError());
	 	return -1;
	 }

	 return 0;
}

int init_well(Well *well)
{
	memset(&well->data,false,sizeof(well->data));
    well->s1 = Mix_LoadWAV("");
	return 0;

}

int init_serpent(Serpent *sp)
{
	memset(&sp->grille,EMPTY,sizeof(sp->grille));

 Pos startPos;
	sp->hd = 0;
	sp->td = 0;
	sp->taille = 1;
	 sp->isAlive = true;
    sp->grow = false;
	startPos.lig = W/2;
	startPos.col = H/2;
  sp->grille[startPos.lig][startPos.col] = SNAKE;
  sp->pos[sp->hd] = startPos;
 
  new_apple(sp);
	
  sp->_direction = RIGHT;
	return 0;
}


void cleanup(void)
{
	 if(window)SDL_DestroyWindow(window),window = NULL;
	 if(renderer)SDL_DestroyRenderer(renderer),renderer = NULL;
	 Mix_CloseAudio();
	 Mix_Quit();
	 IMG_Quit();
	 TTF_Quit();
     SDL_Quit();
}
