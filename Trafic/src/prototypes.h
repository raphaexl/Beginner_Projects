#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include "defs.h"
#include "structs.h"

extern int randomNumber(int min, int max);
extern int negatModulo(int x, int max);

extern int init_SDL(char *title, char *path);
extern int init_Game(void);
extern int loadGame(void);

extern SDL_Renderer *getRenderer(void);
extern SDL_Texture *loadImage(char path[]);
extern int drawImage(SDL_Texture *texture,SDL_Rect pos);
extern int scrollinBackground(SDL_Texture *texture,int x,int speed);
extern Game *getGame(void);
extern int gamePlay(Input *in);
extern Player *getPlayer(void);
extern Enemy *getEnemy(void);
extern int drawGame(void);
extern int draw(void);

extern int collision(SDL_Rect pos1,SDL_Rect pos2);

extern void delay(unsigned int frameLimit );
extern  void gestionInput(Input *in);
extern  void getInput(Input *in);

extern void free_Game(Game *game);
extern void cleanup(void);
#endif