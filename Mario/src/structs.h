#ifndef STRUCTS_H
#define STRUCTS_H

 typedef struct 
 {

   SDL_bool key[SDL_NUM_SCANCODES];
   SDL_bool quit;
  int mousex,mousey,mousexrel,mouseyrel;
  int xwheel, ywheel;
  SDL_bool mouse[6];

 int left, right,up, down;
 }Input;
 typedef struct 
 {
 	int level;
 	int speed;
    SDL_Texture  *menu;
 	SDL_Texture  *fond;
 	SDL_Texture *tuyau1,*tuyau2;
 	SDL_Rect posT1,posT2;
 	Mix_Music *background;
 	Mix_Chunk *tab[5];
 	Mix_Chunk *s;
 }Game;

 typedef struct 
 {
 	int score;
 	SDL_Rect src,dest;
 	SDL_Texture *image;
 	float vy;
 	int w,h;
 	int frameWidth, frameHeight;
 }Player;
 
 #endif