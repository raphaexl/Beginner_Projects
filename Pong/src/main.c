#include "prototypes.h"

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
         Input in;
        Context C;
         SDL_Rect pos1={20,20,50,150};
         SDL_Rect pos2 ={700,20,50,150};
        Paddle paddle1;
        Paddle paddle2;
         Balle balle;
	 int statut = EXIT_FAILURE;
	 bool running = true;

	 if(init("Test1.0"))goto Quit;
	  if(context_init(&C)) goto Quit;
	   if(paddle_init(&paddle1,pos1))return -1;
	   if(paddle_init(&paddle2,pos2))return -1;
	  if(balle_init(&balle,"graphics/rouge.bmp"))return -1;
      puts("Well ! done !");
     memset(&in,SDL_FALSE,sizeof(Input));
	 while(running)
	 {
	 	gestionInput(&in);
	 	game_play(&C,&balle,&paddle1,&paddle2,&in);
	 if(updateRenderer(&C,&balle,&paddle1,&paddle2))goto Quit;
       if(in.quit)running = false;
	 }
     statut = EXIT_SUCCESS;
	 Quit:
	 clean_paddle(&paddle1);
	 clean_paddle(&paddle2);
	 clean_balle(&balle);
	  clean_context(&C);
	 atexit(cleanup);
	 return statut;
}
