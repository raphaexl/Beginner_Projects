#ifndef STRUCTS_H
#define STRUCTS_H

#include "defs.h"



typedef struct
{
	SDL_bool quit;
	SDL_bool key[SDL_NUM_SCANCODES];
	int mousex, mousey, mousexrel, mouseyrel;
	int xwheel,ywheel;
	SDL_bool mouse[6];

}Input;


typedef struct 
{
	bool data[width][height];
  Mix_Chunk *s1;
}Well;

typedef struct 
{
  int lig,col;	
}Pos;

typedef struct 
{
 	
   int hd,td;
   int taille;
   bool isAlive;
   bool grow;

   int grille[W][H];
   Pos pos[MAX_SIZE];
   int _direction;
}Serpent;
#endif