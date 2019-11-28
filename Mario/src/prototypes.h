#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include "defs.h"
#include "structs.h"

extern int randomNumber(int min, int max);
extern int negatModulo(int x, int max);

extern SDL_Window *getWindow(void);
extern int init_SDL(char *title, char *path);
extern int init_game(Game *game,Player *player);


extern SDL_Renderer *getRenderer(void);
extern SDL_Texture *loadImage(char path[]);
extern int drawImage(SDL_Texture *texture,SDL_Rect pos);
extern int drawPlayer(Player *player);
extern int scrollinBackground(SDL_Texture *texture,int x,int speed);
extern Game *getGame(void);
extern int gamePlay(Input *in,Game *game,Player *player);
extern int drawGame(Game *game,Player *player);
extern   int draw(Game *game,Player *player);

extern int collision(SDL_Rect pos1,SDL_Rect pos2);
extern void gravite(Input *in,float factGravite, float factSautMaintenu,Player *player);
extern void controllSol(Player *player);
extern void saute(float impulsion,Player *player);

extern void delay(unsigned int frameLimit );
extern  void gestionInput(Input *in);
extern  void getInput(Input *in);

extern void free_game(Game *game,Player *player);
extern void cleanup(void);
#endif