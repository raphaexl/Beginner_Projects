#include "prototypes.h"



int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	 int statut = EXIT_FAILURE;
	 int go = 1;
       Input in;
      Player player;
     Game game;
	 atexit(cleanup);
	 memset(&in,SDL_FALSE,sizeof(Input));
	 if(init_SDL("Test1.0","graphics/sdl_icone.bmp"))
	 goto Quit; 
	if(init_game(&game,&player))goto Quit;
	 while(go)
	 {
	  gestionInput(&in);
	 if(gamePlay(&in,&game,&player))goto Quit;
	  if(draw(&game,&player)) goto Quit;
       if(in.quit)go = 0;
	 }
	 statut = EXIT_SUCCESS;
    Quit:
    free_game(&game,&player);
    atexit(cleanup);

	 return statut;
}

