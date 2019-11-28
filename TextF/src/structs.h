#ifndef STRUCTS_H
#define STRUCTS_H

  typedef struct 
  {
  	SDL_bool quit;
  	SDL_bool key[SDL_NUM_SCANCODES];
  	int mousex, mousey;
  	int mousexrel, mouseyrel;
  	int xwheel, ywheel;
  	int x,y;
  	SDL_bool mouse[6];
  }Input;
 typedef struct 
 {
   SDL_Texture *message[11];
   TTF_Font *police1,*police2;
   char *text[11];
   SDL_Rect pos[11];
  int w,h;
  int len;
 }Context;

#endif
