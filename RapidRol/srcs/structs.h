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
	float vx,vy;
}Balle;
typedef struct 
{ 
	SDL_Texture *pads[5];
	SDL_Rect pos[5];
    Mix_Music *background;
	double speed;
}Context; 
 #endif
