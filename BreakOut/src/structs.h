#ifndef STRUCTS_H 
#define STRUCTS_H

#include "defs.h"

typedef struct 
{
  SDL_bool key[SDL_NUM_SCANCODES];
  SDL_bool mouse[6];
  SDL_bool quit;
  int mousex,mousey;
  int mousexrel,mouseyrel;	
  int xwheel, ywheel;
}Input;

typedef struct 
{
	SDL_Texture *img;
	SDL_Rect pos;
   float speed;
}Paddle;

typedef struct  
{
	SDL_Texture *img;
    SDL_Rect pos;
   float vx,vy;
  float coeff;
}Balle;

typedef struct 
{
  Mix_Chunk *sd1,*sd2,*sd3,*sd4;
  SDL_Texture *cadre[4];
  SDL_Rect cadPos[4];
  SDL_Texture *img;
  int grille[100][100];
  SDL_Rect pos;
int w,h;
}Context;
#endif
