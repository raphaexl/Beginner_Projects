#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include "defs.h"
#include "structs.h"


  extern int init(char *title);
  extern SDL_Renderer *getRenderer(void);
  extern SDL_Texture *getTexture(void);
  extern SDL_Texture *loadImage(char *path);
  extern int init_context(Context *C);
  extern int init_balle(Balle *balle, char *path);
  extern  void updateEvent(Input *in);
  
  extern  int drawImage(SDL_Texture *image, int x, int y,SDL_Rect pos);
  extern int updateRenderer(Context *C,Balle *balle);

  extern int gamePlay(Context *C,Balle *balle,Input *in);
  extern void saute(Balle *balle,float impulsion);
  extern void gravite(Balle *balle,float factGravite,float factsautmaintenu,Input *in);
  extern int controll(Context *C,Balle *balle);

 extern void clean_context(Context *C);
 extern void clean_balle(Balle *balle);
 extern void cleanup();


 extern int collision(SDL_Rect pos1,SDL_Rect pos2);
 extern int randomNumber(int min, int max);
 extern int negatModulo(int x,int mod);
#endif