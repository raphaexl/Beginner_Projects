
#ifndef STRUCTS_H
#define STRUCTS_H

#include "defs.h"

typedef struct 

{
	SDL_bool key[SDL_NUM_SCANCODES];
	SDL_bool mouse[6];
	SDL_bool quit;

	int mousex,mousey,mousexrel,mouseyrel;
	int xwheel,ywheel;
}Input;

typedef struct 
{
	SDL_Texture *img;
	SDL_Rect pos;
	int vx,vy;
	int coeff;
}Balle;

typedef struct 
{
	SDL_Texture *img;
	SDL_Rect pos;
	double speed;
}Paddle;


typedef  struct 
{
	
    SDL_Texture *cadre[6];
    SDL_Rect pos[6];
   int w,h;
   
}Context;


#endif
