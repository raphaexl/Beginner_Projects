 #ifndef STRUCTS_H
 #define STRUCTS_H

  #include "defs.h"

 typedef struct 
 {
 	 SDL_bool key[SDL_NUM_SCANCODES];
 	 SDL_bool quit;
 	 SDL_bool mouse[6];
 	 int mousex,mousey,mousexrel,mouseyrel;
 	 int xwheel,ywheel;
 }Input;

typedef struct 
{
  SDL_Texture *img;
  SDL_Rect pos;
  float vy;
  float gravite;	
  float elasticite;
}Balle;
typedef struct 
{
 Balle balle[20];	
}Context;
 #endif
