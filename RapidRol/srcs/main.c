#include "prototypes.h"

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv; //for windows
	 int statut = EXIT_FAILURE;
 	 bool running = true;
         Input in;
       Context C;
       Balle balle;
       if(init("Rapide Roll")) goto Quit;
       if(init_context(&C))goto Quit;
       if(init_balle(&balle,"graphics/rouge.bmp")) goto Quit;
       memset(&in,SDL_FALSE,sizeof(Input));
       if(Mix_PlayMusic(C.background,-1))
       {
        fprintf(stderr, "Erreur Mix_PlayMusic()%s\n",Mix_GetError() );
        return -1;
       }
	 while(running)
	 {
       updateEvent(&in);
        gamePlay(&C,&balle,&in);
       if(updateRenderer(&C,&balle)) goto Quit;

       if(in.quit)running = false;
	 }

	 statut = EXIT_SUCCESS;
	 Quit:
	 clean_balle(&balle);
	 clean_context(&C);
	 atexit(cleanup);

	 return statut;
}
