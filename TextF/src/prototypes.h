  #ifndef PROTOTYPES_H
  #define PROTOTYPES_H
    
    #include "defs.h"
    #include "structs.h"


     extern int init(char *title);
     extern int init_Context(Context *C);
     extern SDL_Renderer *getRenderer(void);
     extern SDL_Window *getWindow(void);

     extern void getInput(Input *in);
     extern void gestionInput(Input *in);
     
     extern  int drawImage(SDL_Texture *image, int srcx, int srcy, SDL_Rect dest);
      extern int updateRenderer(Context *C);
    extern  int setWindowColor(void);
   extern int randomNumber(int min, int max);

   extern void free_Context(Context *C);
   extern void cleanup();

  #endif