#include "prototypes.h"


Input in;
Context C;
int main(int argc, char *argv[])
{

   (void)argc;
(void)argv;   
  int statut = EXIT_FAILURE;
    int go = 1;
	  
	  if(init("Test1.0"))
	  goto Quit;
	if(init_Context(&C))goto Quit;
  memset(&in,SDL_FALSE,sizeof(Input));
	  while(go)
	  {
     
     gestionInput(&in);
      if(updateRenderer(&C))goto Quit;
      if(in.quit)go = 0;
	  }

	  statut = EXIT_SUCCESS;

	  Quit:
	  free_Context(&C);
	  atexit(cleanup);
  return statut;
}
