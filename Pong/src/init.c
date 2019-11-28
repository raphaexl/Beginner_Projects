/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 20:38:36 by ebatchas          #+#    #+#             */
/*   Updated: 2019/11/28 15:19:36 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    	fprintf(stderr, " Erreur SDL_Init() %s\n",SDL_GetError() );
    	return -1;
    }

    window = SDL_CreateWindow(title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
    if(!window)
    {
    	fprintf(stderr, "Erreur SDL_CreateWindow() %s\n", SDL_GetError());
    	return -1;
    }
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if(!renderer)
    {
    	fprintf(stderr, "Erreur SDL_CreateRenderer() %s\n", SDL_GetError());
    	return -1;
    }
   
   if(TTF_Init())
   {
   	fprintf(stderr, "Erreur TTF_Init() %s\n", TTF_GetError());
   	return -1;
   }

   
   if(!IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG))
   {
   	fprintf(stderr, "Erreur IMG_Init() %s\n",IMG_GetError() );
   	return -1;
   }
   if(Mix_Init(MIX_INIT_MP3))
   {
   	fprintf(stderr, "Erreur MIX_Init() %s\n",Mix_GetError() );
   	return -1;
   }
   if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048))
   {
   	fprintf(stderr, "Erreur Mix_OpenAudio() %s\n", Mix_GetError());
   	return -1;
   }
   Mix_AllocateChannels(32);
   return 0;
 }

int balle_init(Balle *balle,char *path)
{
   balle->img = loadImage(path);
   if(!balle->img) 
   	return -1;
   if(SDL_QueryTexture(balle->img,NULL,NULL,&balle->pos.w,&balle->pos.h))
   {
   	fprintf(stderr, "Erreur SDL_QueryTexture() %s\n",SDL_GetError() );
   	return -1;
   }
   balle->pos.x = SCREEN_WIDTH/2 +68;
   balle->pos.y = SCREEN_HEIGHT/2+85;
   balle->vx = (int)BALL_START_VX;
   balle->vy = (int)BALL_START_VY;
   balle->coeff = 4;
   return 0;
}

int paddle_init(Paddle *paddle,SDL_Rect pos)
{
	 SDL_Surface *pad = NULL;
	 SDL_Rect rectangle = {0,0,50,150};
	 pad = SDL_CreateRGBSurface(0,32,32,32,0,0,0,0);
	 if(!pad)
	 {
	 	fprintf(stderr, "Erreur SDL_CreateRGBSurface() %s\n",SDL_GetError() );
	 	return -1;
	 }
	 Uint32 color = SDL_MapRGB(pad->format,255,255,255);
	 if(SDL_FillRect(pad,&rectangle,color))
	 {
	 	fprintf(stderr, " Erreur SDL_FillRect() %s\n",SDL_GetError() );
	 	return -1;
	 }
	 SDL_Texture *image = NULL;
   image = SDL_CreateTextureFromSurface(getRenderer(),pad);
	 if(!image)
	 {
	 	fprintf(stderr, "Erreur SDL_CreateTextureFromSuface() %s\n", SDL_GetError());
	 	return -1;
	 }
	 SDL_FreeSurface(pad),pad = NULL;

	 paddle->img = image;
	 paddle->pos.x = pos.x;
	 paddle->pos.y = pos.y;
	 paddle->pos.w = pos.w;
	 paddle->pos.h = pos.h;
   paddle->speed = 0;
  return 0;
}



int context_init(Context *C)
{

	SDL_Surface *carre[6];
	SDL_Rect rectangle = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};

	SDL_GetWindowSize(window,&C->w,&C->h);
    
    for (int i = 0; i < 6; ++i)
    {
    	carre[i] = SDL_CreateRGBSurface(0,32,32,32,0,0,0,0);
    
    }
  
    for (int i = 0; i < 6; ++i)
    {
      if(!carre[i])
      {
        fprintf(stderr, " Erreur SDL_CreateRGBSurface() %s\n", SDL_GetError());
        return -1;
      }
    }
    Uint32 color = SDL_MapRGB(carre[0]->format,255,142,23);
 for (int i = 0; i < 6; ++i)
    {
    	
    	if(SDL_FillRect(carre[i],&rectangle,color))
    	{
    		fprintf(stderr, " Erreur SDL_FillRect()%s\n", SDL_GetError());
    		return -1;
    	}
    }
   
    for (int i = 0; i < 6; ++i)
    {
    	C->cadre[i] = SDL_CreateTextureFromSurface(getRenderer(),carre[i]);
    	if(!C->cadre[i])
    	{
    		fprintf(stderr, " Erreur SDL_CreateTextureFromSuface() %s\n",SDL_GetError() );
    		return -1;
    	}
    }

    for (int i = 0; i < 6; ++i)
    {
    	SDL_FreeSurface(carre[i]),carre[i] = NULL;
    }
    
  C->pos[0].x = 5;
    for(int i=0;i<3;++i)
    C->pos[i].y = 5;
    C->pos[1].x = C->w/2 - 5;
    C->pos[2].x = C->w -15;
     for(int i=0;i<3;++i)
    C->pos[i].w = 10;
     for(int i=0;i<3;++i)
    C->pos[i].h = C->h- 5;
    for(int i=3;i<6;++i)
     C->pos[i].x = 5;
     C->pos[3].y = 5;
     C->pos[4].y = C->h - 15; 
    for(int i=3;i<5;++i)
    C->pos[i].h = 10;
 for(int i=3;i<5;++i)
    C->pos[i].w = C->w - 5;


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
  for (int i = 0; i < 6; ++i)
 SDL_DestroyTexture(C->cadre[i]),C->cadre[i] = NULL;
 
}
 void cleanup(void)
 {
 	 if(renderer)SDL_DestroyRenderer(renderer),renderer = NULL;
 	 if(window)SDL_DestroyWindow(window),window = NULL;
 	 Mix_CloseAudio();
 	 Mix_Quit();
 	 TTF_Quit();
 	 IMG_Quit();
 	 SDL_Quit();
 }
