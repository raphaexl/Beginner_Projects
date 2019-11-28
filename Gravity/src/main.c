#include "prototypes.h"

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	 int statut = EXIT_FAILURE;
 	 bool running = true;
         Input in;
         Context C;
       if(init("Bouncing Balle")) goto Quit;
       if(init_context(&C)) goto Quit;
       memset(&in,SDL_FALSE,sizeof(Input));
	 while(running)
	 {
       updateEvent(&in);
       if(updateRenderer(&C))goto Quit;
       if(in.quit)running = false;
	 }

	 statut = EXIT_SUCCESS;
	 Quit:
	 clean_context(&C);
	 atexit(cleanup);

	 return statut;
}
