#include "prototypes.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
 
SDL_Renderer *getRenderer(void)
{
	return renderer;
}
  SDL_Window *getWindow(void)
  {
  	return window;
  }
int init_SDL(char *title, char *path)
{
	 if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO))
	 {
	 fprintf(stderr,"Erreur Initialisation de La Bibliotheque SDL2 ! %s\n",SDL_GetError());
	 return -1;
	 }

	 window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE|SDL_WINDOW_OPENGL);
	 if(!window)
	 {
	 fprintf(stderr, "Erreur SDL_CreateWindow()%s\n", SDL_GetError());
	 return -1;
	 }

	 renderer = SDL_CreateRenderer(window,-1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	 if(!renderer)
	 {
	 	fprintf(stderr, " Erreur SDL_CreateRenderer()%s\n",SDL_GetError() );
	 	return -1;
	 }
  SDL_Surface *icone = SDL_LoadBMP(path);
	 if(!icone)
	 {
	 	fprintf(stderr, " Erreur SDL_LoadBMP() %s\n",SDL_GetError() );
	 	return -1;
	 }
	 SDL_SetWindowIcon(window,icone);
	 SDL_FreeSurface(icone),icone = NULL;
	 if(!IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF))
	 {
	 	fprintf(stderr, " Erreur IMG_Init() %s\n",IMG_GetError() );
	 	return -1;
	 }

	 if(TTF_Init())
	 {
	 	fprintf(stderr, " Erreur TTF_Init() %s\n",TTF_GetError() );
	 	return -1;
	 }

	 if(Mix_Init(MIX_INIT_MP3))
	 {
	 	fprintf(stderr, " Erreur Mix_Init() %s\n", Mix_GetError());
	 	return -1;
	 }

	 if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048))
	 {
	 	fprintf(stderr, " Erreur Mix_OpenAudio() %s\n",Mix_GetError() );
	 	return -1;
	 }
	 if(!Mix_AllocateChannels(32))
	 {
	 	fprintf(stderr, " Erreur Mix_AllocateChannels() %s\n", Mix_GetError());
	 	return -1;
	 }
	 return 0;
}

int init_game(Game *game,Player *player)
{
	game->level = 2;
	game->speed = 0;
   game->fond = loadImage("graphics/FondEcran.png");
   if(!game->fond) return -1;
   
   game->menu = loadImage("graphics/menuracer.png");
   if(!game->menu) return -1; 
  
    game->s = Mix_LoadWAV("audio/saut.wav");
    if(!game->s)
    {
    	fprintf(stderr, " Erreur Mix_LoadWAV() %s\n", Mix_GetError());
    	return -1;
    }
   /* Init Player */
   player->score = 0;
    player->image= loadImage("graphics/rabidja.png");
   
   if(SDL_QueryTexture(player->image,NULL,NULL,&player->w,&player->h))
   {
   	fprintf(stderr, " Erreur SDL_QueryTexture() %s\n", SDL_GetError());
   	return -1;
   }
   player->frameWidth = player->w/8;
   player->frameHeight = player->h/5;
   player->src.x =  0;
   player->src.y = player->frameHeight;
    player->src.w = player->frameWidth;
   player->src.h = player->frameHeight;
   player->dest.x = player->dest.y = 275;
   player->dest.w = player->frameWidth;
   player->dest.h = player->frameHeight;

   /* Init Enemys*/
  
  
   
 game->tuyau1 = loadImage("graphics/tuyauHaut.png");
 game->tuyau2 = loadImage("graphics/tuyauBas.png");
 if(SDL_QueryTexture(game->tuyau1,NULL,NULL,&game->posT1.w,&game->posT1.h))
   {
   	fprintf(stderr, " Erreur SDL_QueryTexture() %s\n", SDL_GetError());
   	return -1;
   }
   if(SDL_QueryTexture(game->tuyau2,NULL,NULL,&game->posT2.w,&game->posT2.h))
   {
   	fprintf(stderr, " Erreur SDL_QueryTexture() %s\n", SDL_GetError());
   	return -1;
   }
 game->posT1.x =  SCREEN_WIDTH/2;
 game->posT1.y =  200;
 game->posT2.x =  SCREEN_WIDTH;
 game->posT2.y =   180;
   return 0; 
}


void free_game(Game *game,Player *player)
{
	 if(game->menu)SDL_DestroyTexture(game->menu), game->menu = NULL;
	
	 if(game->fond)SDL_DestroyTexture(game->fond), game->fond= NULL;
	 if(game->s)Mix_FreeChunk(game->s),game->s = NULL;
	 if(player->image) SDL_DestroyTexture(player->image);
     if(game->tuyau1)SDL_DestroyTexture(game->tuyau1);
     if(game->tuyau2)SDL_DestroyTexture(game->tuyau2);
   
}
void cleanup(void)
{
     
	 if(renderer)SDL_DestroyRenderer(getRenderer());
	 if(window)SDL_DestroyWindow(window);
	 Mix_CloseAudio();
	 IMG_Quit();
	 Mix_Quit();
	 TTF_Quit();
	 SDL_Quit();
}