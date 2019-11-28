 #include "prototypes.h"

 int main(int arg, char *argv[])
 {
	 (void)arg;
	 (void)argv;
     int statut = EXIT_FAILURE;
     SDL_bool running = SDL_TRUE;
     
     Input in;
     Well well;
     Serpent sp;
     if(init("Essai Snake!")) goto Quit;
      memset(&in,SDL_FALSE,sizeof(Input));
       if(init_well(&well))goto Quit;
       if(init_serpent(&sp)) goto Quit;
      while(running)
      {
        gestionInput(&in,&sp);
       if(draw(&well,&sp))goto Quit;
      if(in.quit)running = SDL_FALSE;
      }

      statut = EXIT_SUCCESS;
      Quit:
      atexit(cleanup);

      return statut;
 }
