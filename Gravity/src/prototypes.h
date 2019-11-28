#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include "defs.h"
#include "structs.h"


  extern int init(char *title);
  extern int init_context(Context *C);
  extern SDL_Renderer *getRenderer(void);
  extern SDL_Texture *getTexture(void);
  extern SDL_Texture *loadImage2(char *path);
  extern SDL_Texture *loadImage(char *path);
  extern int drawImage(SDL_Texture *image,int x, int y, SDL_Rect pos);
  extern int updateRenderer(Context *C);
  extern  void updateEvent(Input *in);


 extern void clean_context(Context *C);
 extern void cleanup();
#endif
