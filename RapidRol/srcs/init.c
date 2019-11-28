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
	 SDL_Surface *pad[5];
	 SDL_Rect rectangle = {0,0,150,25};

	 for (int i = 0; i < 5; ++i)
	 {
	 	pad[i] = SDL_CreateRGBSurface(0,32,32,32,0,0,0,0);
	 	if(!pad[i])
	 	{
	 		fprintf(stderr, "Erreur SDL_CreateRGBSurface() %s\n",SDL_GetError() );
	 		return -1;
	 	}
	 }
	 Uint32 color = SDL_MapRGB(pad[0]->format,0,255,0);
   
   for (int i = 0; i < 5; ++i)
   {
   	if(SDL_FillRect(pad[i],&rectangle,color))
   	{
   		fprintf(stderr, " Erreur SDL_FillRect() %s\n", SDL_GetError());
   		return -1;
   	}
   }

   for (int i = 0; i < 5; ++i)
   {
   C->pads[i] = SDL_CreateTextureFromSurface(getRenderer(),pad[i]);
   if(!C->pads[i])
   {
   	fprintf(stderr, "Erreur SDL_CreateTextureFromSurface() %s\n", SDL_GetError());
   	return -1;
   }
   }
   for (int i = 0; i < 5; ++i)
   {
  SDL_FreeSurface(pad[i]),pad[i] = NULL;
   }

   for (int i = 0; i < 5; ++i)
   {
   	C->pos[i].w = 150;
   	C->pos[i].h = 25;
   }
  
  C->pos[0].x = 10;
  C->pos[0].y = 5;
  for (int i = 1; i < 4; ++i)
  {
  	C->pos[i].x = C->pos[i-1].x + C->pos[i-1].w + randomNumber(0,10);
  	C->pos[i].y = C->pos[i-1].y + C->pos[i-1].w + randomNumber(20,50);
  }
  C->pos[4].x = SCREEN_WIDTH -C->pos[3].x + C->pos[3].w + randomNumber(0,10);
  	C->pos[4].y =  randomNumber(20,50);
  C->speed = 12.0;
  
  C->background = Mix_LoadMUS("audio/happy_game_theme_loop.ogg");
  if(!C->background)
  {
  	fprintf(stderr, "Erreur Mix_LoadMUS("")%s\n",Mix_GetError() );
  	return -1;
  }
  return 0;

}

int init_balle(Balle *balle, char *path)
{
   balle->img = loadImage(path);
   if(!balle->img)
   	return -1;
   if(SDL_QueryTexture(balle->img,NULL,NULL,&balle->pos.w,&balle->pos.h))
   {
   	fprintf(stderr, "Erreur SDL_QueryTexture() %s\n",SDL_GetError() );
   	return -1;
   }
   balle->pos.x = 50;
   balle->pos.y = 50;
   return 0;
}



SDL_Texture *loadImage(char *path)
{
	SDL_Surface *temp = NULL;
	temp = IMG_Load(path);
	if(!temp)
	{
		fprintf(stderr, "Erreur IMG_Load() %s\n", IMG_GetError());
		return NULL;
	}
	if(SDL_SetColorKey(temp,SDL_TRUE,SDL_MapRGB(temp->format,255,255,255)))
	{
		fprintf(stderr, "Erreur SDL_SetColorKey()%s\n", SDL_GetError());
		return NULL;
	}
	SDL_Texture *image = NULL;
	image = SDL_CreateTextureFromSurface(getRenderer(),temp);
	if(!image)
	{
		fprintf(stderr, "Erreur SDL_CreateTextureFromSuface() %s\n", SDL_GetError());
		return NULL;
	}
	SDL_FreeSurface(temp),temp = NULL;
	return image;
}


void clean_balle(Balle *balle)
{
	SDL_DestroyTexture(balle->img),balle->img = NULL;
}
void clean_context(Context *C)
{
	for (int i = 0; i < 5; ++i)
	{
		SDL_DestroyTexture(C->pads[i]),C->pads[i] = NULL;
	}
	Mix_FreeMusic(C->background);
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
