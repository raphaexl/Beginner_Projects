#include "prototypes.h"

Input in;
int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	 int statut = EXIT_FAILURE;
	 int go = 1;

	 atexit(cleanup);
	 memset(&in,SDL_FALSE,sizeof(Input));
	 if(init_SDL("Traffic1.0","graphics/sdl_icone.bmp"))
	 goto Quit; 
	if(loadGame())goto Quit;
	
	 while(go)
	 {
	  gestionInput(&in);
	 if(gamePlay(&in))goto Quit;
	  if(draw()) goto Quit;
     
     
       if(in.quit)go = 0;
	 }
	 statut = EXIT_SUCCESS;
    Quit:
    atexit(cleanup);

	 return statut;
}
