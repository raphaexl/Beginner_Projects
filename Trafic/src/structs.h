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
 	SDL_Texture  *road[3];
 	SDL_Texture  *track;
 }Game;

 typedef struct 
 {
 	int score;
 	SDL_Rect pos;
 	SDL_Texture *car;
 }Player;
 typedef struct 
 {
 	SDL_Texture *cars[17];
 	SDL_Texture *car1,*car2;
 	SDL_Rect pos1,pos2;
 	int speed;
 }Enemy;
 #endif