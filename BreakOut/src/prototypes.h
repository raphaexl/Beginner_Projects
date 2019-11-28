#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include "structs.h"
#include "defs.h"

   extern int init(char *title);
   extern  int init_context(char path[],Context *C);
   extern  int init_paddle(char path[],Paddle *paddle);
   extern int init_balle(char *path,Balle *balle);
   extern SDL_Renderer *getRenderer(void);
   extern SDL_Window *getWindow(void);
   extern  int SDL_SetWindowColor(SDL_Color color);
   extern SDL_Texture *loadImage(char *path,int R, int G,int B);

   extern void updateEvent(Input *in);
 
   extern void update_balle(Context *C,Balle *balle,Paddle *paddle);
   extern  int updateContext(Context *C);
   extern void gamePlay(Context *C,Balle *balle,Paddle *paddle,Input *in);
   extern int drawImage(SDL_Texture *image,int x, int y, SDL_Rect pos);
   extern int draw(Context *C,Balle *balle,Paddle *paddle);
   
   
   extern  int collision(SDL_Rect ball, SDL_Rect pad);
   extern   int collisionOne(SDL_Rect pos1,SDL_Rect pos2);
   extern  int randomNumber(int min, int max);
   extern  Uint32 time_left(Uint32 nextime);

   extern  void delay(unsigned int framLimits);
   extern void ensure_balle_speed(Balle *balle);
   extern void slow_paddle_down(Paddle *paddle);
   extern  void clean_paddle(Paddle *paddle);
   extern  void clean_balle(Balle *balle);
   extern  void clean_context(Context *C);
   extern void cleanup(void);
#endif