 #include "prototypes.h"


 int main(int argc, char *argv[])
 {
	 (void)argc;
	 (void)argv;
      int statut = EXIT_FAILURE;
      unsigned int framLimits = SDL_GetTicks()+16;
      bool running = true;
      Balle balle;
      Paddle paddle;
      Context C;
      Input in;
      if(init("BreakOut!")) goto Quit;
      if(init_context("graphics/side.png",&C))goto Quit;
      if(init_balle("graphics/balle.bmp",&balle))goto Quit;
      if(init_paddle("graphics/paddle.png",&paddle)) goto Quit;
      memset(&in,SDL_FALSE,sizeof(Input));
      while(running)
      {
           updateEvent(&in);
          gamePlay(&C,&balle,&paddle,&in);
          if(draw(&C,&balle,&paddle))goto Quit;

          delay(framLimits);
          framLimits = SDL_GetTicks()+16;
           if(in.quit)running = false;
      }

      statut = EXIT_SUCCESS;
      
      Quit:
      clean_balle(&balle);
      clean_paddle(&paddle);
      clean_context(&C);
      atexit(cleanup);

      return statut;

 }
