#ifndef PROTOTYPES_H 
#define PROTOTYPES_H

#include "structs.h"
#include "defs.h"

extern  int init(char *title);
extern int context_init(Context *C);

extern int paddle_init(Paddle *paddle,SDL_Rect pos);
extern int balle_init(Balle *balle,char *path);
extern SDL_Window *getWindow(void);
extern  SDL_Renderer *getRenderer(void);

extern  void gestionInput(Input *in);
extern void  updatevent(Input *in);

extern SDL_Texture *loadImage(char *path);

extern int draw_image(SDL_Texture *image,int x,int y,SDL_Rect pos);
extern int updateRenderer(Context *C,Balle *balle,Paddle *paddle1,Paddle *paddle2);


extern  void paddle_slow_down(Paddle *paddle);
extern  void balle_ensure_speed(Balle *balle);
extern  void paddle_update(Paddle *paddle,Context *C);
extern    void game_play( Context *C,Balle *balle,Paddle *paddle1,Paddle *paddle2,Input *in);
extern    void game_update(Balle *balle,Paddle *paddle,Context *C);

extern  int randomNumber(int min, int max);
extern  int collision(SDL_Rect ball, SDL_Rect pad);
extern  Uint32 time_left(Uint32 nextime);

extern void clean_paddle(Paddle *paddle);
extern void clean_balle(Balle *balle);
extern void clean_context(Context *C);
extern  void cleanup(void);
#endif
