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

int init(char *title)
{
	 
	 if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO))
	 {
	 	fprintf(stderr, "Erreur SDL_Init() %s\n", SDL_GetError());
	 	return -1;
	 }
	 window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
	 if(!window)
	 {
	 	fprintf(stderr, "Erreur SDL_CreateWindow() %s\n",SDL_GetError() );
	 	return -1;
	 }
	 renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	 if(!renderer)
	 {
	 	fprintf(stderr, "Erreur SDL_CreateRenderer() %s\n",SDL_GetError() );
	 	return -1;
	 }

	 if(TTF_Init())
	 {
	 	fprintf(stderr, "Erreur TTF_Init() %s\n",TTF_GetError() );
	 	return -1;
	 }
   if(!IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG))
   {
   	fprintf(stderr, "Erreur IMG_Init() %s\n",IMG_GetError( ));
   	return -1;
   }

   if(Mix_Init(MIX_INIT_MP3))
   {
   	fprintf(stderr, "Erreur Mix_Init() %s\n",Mix_GetError() );
   	return -1;
   }
   if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024))
   {
   	fprintf(stderr, "Erreur Mix_OpenAudio() %s\n",Mix_GetError() );
   	return -1;
   }

   Mix_AllocateChannels(32);
   SDL_Surface *ico = NULL;
   ico = SDL_LoadBMP("graphics/sdl_icone.bmp");
   if(!ico)
   {
    fprintf(stderr, "Erreur SDL_LoadBMP() %s\n",SDL_GetError());
    return -1;
   }
   if(SDL_SetColorKey(ico,SDL_TRUE,SDL_MapRGB(ico->format,0,0,0)))
   {
    fprintf(stderr, "Erreur SDL_SetColorKey() %s\n", SDL_GetError());
    return -1;
   }
   SDL_SetWindowIcon(window,ico);
   SDL_FreeSurface(ico),ico = NULL;
   return 0;
}

int init_balle(char *path,Balle *balle)
 {
     balle->img = loadImage(path,0,0,0);
     if(!balle->img)
     	return -1;
     balle->pos.x = SCREEN_HEIGHT/2;
     balle->pos.y = SCREEN_WIDTH/2;
     if(SDL_QueryTexture(balle->img,NULL,NULL,&balle->pos.w,&balle->pos.h))
     {
     	fprintf(stderr, "Erreur SDL_QueryTexture() %s\n", SDL_GetError());
     	return -1;
     }
     balle->vx = BALLE_START_VX;
      balle->vy = BALLE_START_VY;
      balle->coeff = 4.0;
     return 0;
 }
 int init_paddle(char path[],Paddle *paddle)
 {
 	 paddle->img = loadImage(path,255,255,255);
 	 if(!paddle->img)
 	 	return -1;
 	 if(SDL_QueryTexture(paddle->img,NULL,NULL,&paddle->pos.w,&paddle->pos.h))
 	 {
 	 	fprintf(stderr, "Erreur SDL_QueryTexture() %s\n", SDL_GetError());
 	 	return -1;
 	 }
 	 paddle->pos.x = SCREEN_WIDTH/2 - paddle->pos.w/2;
 	 paddle->pos.y = SCREEN_HEIGHT - paddle->pos.h -5;
 	 paddle->speed = 0.0;
 	 return 0;
 }
 int init_context(char path[],Context *C)
 {
 	 SDL_Surface *temp[2];
 	 SDL_Rect rectangle = {0,0,SCREEN_WIDTH,16};
 	 for (int i = 0; i < 2; ++i)
 	 {
 	 	C->cadre[i] = loadImage(path,0,0,0);
 	 	if(!C->cadre[i])
 	 		return -1;
 	 }
 	 for (int i = 0; i < 2; ++i)
 	 {
 	 	temp[i] = SDL_CreateRGBSurface(0,32,32,32,0,0,0,0);
 	 	if(!temp[i])
 	 	{
 	 		fprintf(stderr, "Erreur SDL_CreateRGBSurface() %s\n",SDL_GetError());
 	 		return -1;
 	 	}
 	 }
 	Uint32 color = SDL_MapRGB(temp[0]->format,255,142,23);
 	 for (int i = 0; i < 2; ++i)
 	 {
 	 	if(SDL_FillRect(temp[i],&rectangle,color)) 
 	 	{
 	 		fprintf(stderr, "Erreur SDL_FillRect() %s\n",SDL_GetError() );
 	 		return -1;
 	 	}
 	 }

 	 for (int i = 0; i < 2; ++i)
 	 {
 	 	C->cadre[i+2] = SDL_CreateTextureFromSurface(getRenderer(),temp[i]);
 	 	if(!C->cadre[i+2])
 	 	{
 	 		fprintf(stderr, "Erreur SDL_CreateTextureFromSurface() %s\n",SDL_GetError() );
 	 		return -1;
 	 	}
 	 	C->cadPos[i+2].w = SCREEN_WIDTH;
 	 	C->cadPos[i+2].h = 16;
 	 }

 	 for (int i = 0; i < 2; ++i)
 	 {
 	 	SDL_FreeSurface(temp[i]),temp[i] = NULL;
 	 }
    for (int i = 0; i < 2; ++i)
    {
    	/* code */
    	if(SDL_QueryTexture(C->cadre[i],NULL,NULL,&C->cadPos[i].w,&C->cadPos[i].h))
    	{
    		fprintf(stderr, "Erreur SDL_QueryTexture() %s\n", SDL_GetError());
    		return -1;
    	}
    
    }
    C->cadPos[0].x = C->cadPos[0].y = 0;
    C->cadPos[2].x = C->cadPos[2].y = 0;
    C->cadPos[1].x = SCREEN_WIDTH - C->cadPos[1].w;
     C->cadPos[1].y = 0;
    C->cadPos[3].x = 0;
     C->cadPos[3].y = SCREEN_HEIGHT - C->cadPos[3].h;
     for (int i = 0; i < 100; ++i)
     {
       /* code */
      for (int j = 0; j < 100; ++j)
      {
       C->grille[i][j] = 1;
      }
     }
     
     SDL_GetWindowSize(window,&C->w,&C->h);
    
       C->img = loadImage("graphics/bricks.png",255,255,255);
      C->sd1 = Mix_LoadWAV("audio/sonnerie.wav");
      C->sd2 = Mix_LoadWAV("audio/s.wav");
      C->sd3 = Mix_LoadWAV("audio/s1.wav");
      C->sd4 = Mix_LoadWAV("audio/s2.wav");
      if(!C->sd1||!C->sd2||!C->sd3||!C->sd4)
      {
        fprintf(stderr, "Erreur Mix_LoadWAV()%s\n",SDL_GetError());
        return -1;
      }
    
return 0;
 }
 void clean_balle(Balle *balle)
 {
 	if(balle->img)SDL_DestroyTexture(balle->img),balle->img = NULL;
 }
 void clean_paddle(Paddle *paddle)
 {
 	if(paddle->img)SDL_DestroyTexture(paddle->img),paddle->img = NULL;
 }
 void clean_context(Context *C)
 {
 	 for (int i = 0; i < 4; ++i)
 	 {
 	 	if(C->cadre[i])SDL_DestroyTexture(C->cadre[i]),C->cadre[i] = NULL;
 	 }
   if(C->img)SDL_DestroyTexture(C->img),C->img = NULL;
   if(C->sd1)Mix_FreeChunk(C->sd1),C->sd1 = NULL;
   if(C->sd2)Mix_FreeChunk(C->sd2),C->sd2 = NULL;
   if(C->sd3)Mix_FreeChunk(C->sd3),C->sd3 = NULL;
   if(C->sd4)Mix_FreeChunk(C->sd4),C->sd4 = NULL;
 }
void cleanup(void)
{
	 if(renderer)SDL_DestroyRenderer(renderer),renderer = NULL;
	 if(window)SDL_DestroyWindow(window),window = NULL;
	 Mix_CloseAudio();
	 Mix_Quit();
	 IMG_Quit();
	 TTF_Quit();
	 SDL_Quit();
}
