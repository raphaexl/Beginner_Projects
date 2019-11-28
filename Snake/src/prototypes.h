#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include "defs.h"
#include "structs.h"

  extern int init(char *title);
  extern int init_well(Well *well);
  extern int init_serpent(Serpent *sp);
  extern SDL_Renderer *getRenderer(void);
  
  extern int draw(Well *well,Serpent *sp);
  extern void gestionInput(Input *in,Serpent *sp);
  extern void updateEvent(Input *in);

  extern int well_display(Well *well,Serpent *sp);
  extern int serpent_display(Serpent *sp);
  
  extern bool snake_evolue(Serpent *sp);
  extern int serpent_move(Serpent *sp);
  extern int rotate(Serpent *sp);
  extern int new_apple(Serpent *sp);

 
  extern SDL_Texture *loadImage(char path[],int R,int G,int B);
  extern int drawImage(SDL_Texture *image,int x, int y,SDL_Rect pos);
 
  extern int randomNumber(int min, int max);
  extern void cleanup(void);
#endif
