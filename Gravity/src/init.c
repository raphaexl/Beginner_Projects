#include "prototypes.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

SDL_Window *getWindow(void)
{
	return window;
}

SDL_Renderer *getRenderer(void)
{
	return renderer;
}

int init(char title[])
{
	 if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO))
	 {
	 	fprintf(stderr, " Erreur SDL_Init() %s\n", SDL_GetError());
	 	return -1;
	 }
	 window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);
	 if(!window)
	 {
	 	fprintf(stderr, " Erreur SDL_CreateWindow() %s\n", SDL_GetError());
	 	return -1;
	 }
	 renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	 if(!renderer)
	 {
	 	fprintf(stderr, "Erreur SDL_CreateRenderer() %s\n",SDL_GetError() );
	 	return -1;
	 }

	 if(!IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG))
	 {
	 	fprintf(stderr, "Erreur IMG_Init() %s\n",IMG_GetError());
	 	return -1;
	 }

	 if(TTF_Init())
	 {
	 	fprintf(stderr, "Erreur TTF_Init() %s\n",TTF_GetError());
	 	return -1;
	 }

	 if(Mix_Init(MIX_INIT_MP3))
	 {
	 	fprintf(stderr, "Erreur Mix_Init() %s\n", Mix_GetError());
	 	return -1;
	 }

	 Mix_AllocateChannels(32);
	 if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048))
	 {
	 	fprintf(stderr, "Erreur Mix_OpenAudio() %s\n", Mix_GetError());
	 	return -1;
	 }

	 return 0;
}

int init_context(Context *C)
{
    for (int i = 0; i < 5; ++i)
     {
     if(i==0)
     	{
     		C->balle[i].img = loadImage("graphics/rouge.bmp");
     		C->balle[i+5].img = loadImage("graphics/rouge.bmp");
     		C->balle[i+10].img = loadImage("graphics/rouge.bmp");
     		C->balle[i+15].img = loadImage("graphics/rouge.bmp");
     	}
     else  if(i==1)
     	{
     		C->balle[i].img = loadImage2("graphics/balle.bmp");
     		C->balle[i+5].img = loadImage2("graphics/balle.bmp");
     		C->balle[i+10].img = loadImage2("graphics/balle.bmp");
     		C->balle[i+15].img = loadImage2("graphics/balle.bmp");
     	}
     	 else  if(i==2)
     	{
     		C->balle[i].img = loadImage("graphics/vert.bmp");
     		C->balle[i+5].img = loadImage("graphics/vert.bmp");
     		C->balle[i+10].img = loadImage("graphics/vert.bmp");
     		C->balle[i+15].img = loadImage("graphics/vert.bmp");
     	}
     	 else  if(i==3)
     	{
     		C->balle[i].img = loadImage("graphics/jaune.bmp");
     		C->balle[i+5].img = loadImage("graphics/jaune.bmp");
     		C->balle[i+10].img = loadImage("graphics/jaune.bmp");
     		C->balle[i+15].img = loadImage("graphics/jaune.bmp");
     	}
     	 else  if(i==4)
     	{
     		C->balle[i].img = loadImage("graphics/bleu.bmp");
     		C->balle[i+5].img = loadImage("graphics/bleu.bmp");
     		C->balle[i+10].img = loadImage("graphics/bleu.bmp");
     		C->balle[i+15].img = loadImage("graphics/bleu.bmp");
     	}
     	
     if(!C->balle[i].img) return -1;
     } 
      C->balle[0].pos.x = 0;
      C->balle[0].pos.y = 0; 
      if(SDL_QueryTexture(C->balle->img,NULL,NULL,&C->balle[0].pos.w,&C->balle[0].pos.h))
      {
      	fprintf(stderr, "Erreur SDL_QueryTexture() %s\n", SDL_GetError());
      	return -1;
      }
      for (int i = 1; i < 20; ++i)
      {
       C->balle[i].pos.x =  C->balle[i-1].pos.x + C->balle[i-1].pos.w;
       C->balle[i].pos.y = 0; 
        C->balle[i].pos.w =  C->balle[i-1].pos.w;
      C->balle[i].pos.h = C->balle[i-1].pos.h; 
      C->balle[i].vy = 0;
      C->balle[i].gravite = 0.04;
      C->balle[i].elasticite = (float)i/20;
      }
       C->balle[0].vy = 0;
      C->balle[0].gravite = 0.04;
       C->balle[0].elasticite = .0/20;
 return 0;
}

void clean_context(Context *C)
{
	for (int i = 0; i < 20; ++i)
	{
		if(C->balle[i].img)SDL_DestroyTexture(C->balle[i].img),C->balle[i].img = NULL;
	}
}

void cleanup(void)
{
	SDL_DestroyRenderer(renderer),renderer = NULL;
	SDL_DestroyWindow(window),window = NULL;
	IMG_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}