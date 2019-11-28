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
    case SDL_QUIT: in->quit = SDL_TRUE;
    break;
    case SDL_KEYDOWN:
    switch(event.key.keysym.scancode)
    {
    	case SDL_SCANCODE_Q:in->quit = SDL_TRUE;
    	break;
    	case SDL_SCANCODE_ESCAPE:in->quit = SDL_TRUE;
    	break;
    	case SDL_SCANCODE_UP:in->up = 1;
    	break;
      case SDL_SCANCODE_SPACE:in->up = 1;
      break;
    	case SDL_SCANCODE_DOWN: in->down = 1;
    	break;
    	case SDL_SCANCODE_RIGHT:in->right = 1;
    	break;
    	case SDL_SCANCODE_LEFT:in->left = 1;
    	break;
    	default: in->key[event.key.keysym.scancode] = SDL_TRUE;
    	break;
     
    }
    break;
    case SDL_KEYUP:
    switch(event.key.keysym.scancode)
    {
    	case SDL_SCANCODE_Q:in->quit = SDL_FALSE;
    	break;
    	case SDL_SCANCODE_ESCAPE:in->quit = SDL_FALSE;
    	break;
    	case SDL_SCANCODE_UP:in->up = 0;
    	break;
      case SDL_SCANCODE_SPACE:in->up = 0;
      break;
    	case SDL_SCANCODE_DOWN: in->down = 0;
    	break;
    	case SDL_SCANCODE_RIGHT:in->right = 0;
    	break;
    	case SDL_SCANCODE_LEFT:in->left = 0;
    	break;
    	default: in->key[event.key.keysym.scancode] = SDL_FALSE;
    	break;
    }
    break;
   case SDL_MOUSEBUTTONDOWN:
   in->mouse[event.button.button] = SDL_TRUE;
   break;
   case SDL_MOUSEBUTTONUP:
   in->mouse[event.button.button] = SDL_FALSE;
   break;
  case SDL_MOUSEMOTION:
  {
  in->mousex = event.motion.x;
  in->mousey = event.motion.y;
  in->mousexrel = event.motion.xrel;
  in->mouseyrel = event.motion.yrel;
   }
   break;
   case SDL_MOUSEWHEEL:
   {
   in->xwheel = event.wheel.x;
   in->ywheel = event.wheel.y;
    }
    }
  }

  }