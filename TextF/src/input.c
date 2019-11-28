
#include "prototypes.h"

void gestionInput(Input *in)
{
	 getInput(in);
}

void getInput(Input *in)
 {
     SDL_Event event;
     while(SDL_PollEvent(&event))
     {
     switch(event.type)
     {
     case SDL_QUIT:
     in->quit = SDL_TRUE;
     break;
     case SDL_KEYDOWN:
     in->key[event.key.keysym.scancode] = SDL_TRUE;
     break;
     case SDL_KEYUP:
     in->key[event.key.keysym.scancode] = SDL_FALSE;
     break;
     case SDL_MOUSEMOTION:
     {
     	in->mousex = event.motion.x;
     	in->mousey = event.motion.y;
     	in->mousexrel =  event.motion.xrel;
     	in->mouseyrel = event.motion.yrel;
     }
     break;
     case SDL_MOUSEWHEEL:
     {
     	in->xwheel = event.wheel.x;
     	in->ywheel = event.wheel.y;
     }
     break;
     case SDL_MOUSEBUTTONDOWN:
     in->mouse[event.button.button] = SDL_TRUE;
     break;
     case SDL_MOUSEBUTTONUP:
     in->mouse[event.button.button] = SDL_FALSE;
     break;
      default:break;
     }
     }
 }