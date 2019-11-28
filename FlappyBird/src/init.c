#include "prototypes.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
  Game game;
  Player player;
  Enemy enemy;
SDL_Renderer *getRenderer(void)
{
	return renderer;
}
Game *getGame(void)
{
	return &game;
}
Player *getPlayer(void)
{
	return &player;
}
Enemy *getEnemy(void)
{
	return &enemy;
}
int init_SDL(char *title, char *path)
{
	 if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO))
	 {
	 fprintf(stderr,"Erreur Initialisation de La Bibliotheque SDL2 ! %s\n",SDL_GetError());
	 return -1;
	 }

	 window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE|SDL_WINDOW_OPENGL);
	 if(!window)
	 {
	 fprintf(stderr, "Erreur SDL_CreateWindow()%s\n", SDL_GetError());
	 return -1;
	 }

	 renderer = SDL_CreateRenderer(window,-1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	 if(!renderer)
	 {
	 	fprintf(stderr, " Erreur SDL_CreateRenderer()%s\n",SDL_GetError() );
	 	return -1;
	 }
  SDL_Surface *icone = SDL_LoadBMP(path);
	 if(!icone)
	 {
	 	fprintf(stderr, " Erreur SDL_LoadBMP() %s\n",SDL_GetError() );
	 	return -1;
	 }
	 SDL_SetWindowIcon(window,icone);
	 SDL_FreeSurface(icone),icone = NULL;
	 if(!IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF))
	 {
	 	fprintf(stderr, " Erreur IMG_Init() %s\n",IMG_GetError() );
	 	return -1;
	 }

	 if(TTF_Init())
	 {
	 	fprintf(stderr, " Erreur TTF_Init() %s\n",TTF_GetError() );
	 	return -1;
	 }

	 if(Mix_Init(MIX_INIT_MP3))
	 {
	 	fprintf(stderr, " Erreur Mix_Init() %s\n", Mix_GetError());
	 	return -1;
	 }

	 if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048))
	 {
	 	fprintf(stderr, " Erreur Mix_OpenAudio() %s\n",Mix_GetError() );
	 	return -1;
	 }
	 if(!Mix_AllocateChannels(32))
	 {
	 	fprintf(stderr, " Erreur Mix_AllocateChannels() %s\n", Mix_GetError());
	 	return -1;
	 }
	 return 0;
}

int init_Game(void)
{
	game.level = 2;
	game.speed = 0;
   game.fond = loadImage("graphics/bandeFondEcran.png");
   if(!game.fond) return -1;
   
   game.menu = loadImage("graphics/menuracer.png");
   if(!game.menu) return -1; 
  game.background = Mix_LoadMUS("audio/Temajogoportfolio.mp3");
   if(!game.background) 
   {
   	fprintf(stderr, " Erreur Mix_LoadMUS() %s\n",Mix_GetError() );
   	return -1;
   }
   game.play = false;
  game.s = Mix_LoadWAV("audio/battementAile.wav");
    game.tab[0] = Mix_LoadWAV("audio/battementAile.wav");
   game.tab[1] = Mix_LoadWAV("audio/choc.wav");
   game.tab[2] = Mix_LoadWAV("audio/sonnerie.wav");
   game.tab[3] = Mix_LoadWAV("audio/jumpEffect.wav");
   game.tab[4] = Mix_LoadWAV("audio/laserEffect.wav");
   
   for (int i = 0; i < 5; ++i)
   {
   if(!game.tab[i])
   {
   	fprintf(stderr, " Erreur Mix_LoadWAV() %s\n",Mix_GetError() );
   return -1;
   }
   }
   /* Init Player */
   player.score = 0;
    player.current = loadImage("graphics/Oiseau1.png");
   if(!player.current) return -1;
   player.bird1 = loadImage("graphics/Oiseau1.png");
   if(!player.bird1) return -1;
    player.bird2 = loadImage("graphics/Oiseau2.png");
   if(!player.bird2) return -1;
   if(SDL_QueryTexture(player.bird1,NULL,NULL,&player.posO.w,&player.posO.w))
   {
   	fprintf(stderr, " Erreur SDL_QueryTexture() %s\n", SDL_GetError());
   	return -1;
   }
   player.posO.x = SCREEN_WIDTH/2 - player.posO.w/2;
   player.posO.y  =  SCREEN_HEIGHT/2 - player.posO.h/2 ;

   /* Init Enemys*/
  
   enemy.speed = 0;
   
 enemy.tuyau1 = loadImage("graphics/tuyauHaut.png");
 enemy.tuyau2 = loadImage("graphics/tuyauBas.png");
 if(SDL_QueryTexture(enemy.tuyau1,NULL,NULL,&enemy.posT1.w,&enemy.posT1.h))
   {
   	fprintf(stderr, " Erreur SDL_QueryTexture() %s\n", SDL_GetError());
   	return -1;
   }
 enemy.posT1.x =  SCREEN_WIDTH/2;
 enemy.posT1.y =  -200;
  enemy.posT2.x =  SCREEN_WIDTH/2;
 enemy.posT2.y =  (enemy.posT1.y + enemy.posT1.h) + 180;
   return 0; 
}

int loadGame(void)
{
	if(init_Game())return -1;
	return 0;
}
void free_Game(Game *game)
{
	 if(game->menu)SDL_DestroyTexture(game->menu), game->menu = NULL;
	
	 if(game->fond)SDL_DestroyTexture(game->fond), game->fond= NULL;
	 if(getPlayer()->current) SDL_DestroyTexture(getPlayer()->current);
     if(getPlayer()->bird1) SDL_DestroyTexture(getPlayer()->bird1);
     if(getPlayer()->bird2) SDL_DestroyTexture(getPlayer()->bird2);
     if(getEnemy()->tuyau1)SDL_DestroyTexture(getEnemy()->tuyau1);
     if(getEnemy()->tuyau2)SDL_DestroyTexture(getEnemy()->tuyau2);
    if(game->background)Mix_FreeMusic(game->background),game->background = NULL;
 for (int i = 0; i < 5; ++i)
     {
     	if(game->tab[i])Mix_FreeChunk(game->tab[i]),game->tab[i] = NULL;
     }
     if(game->s)Mix_FreeChunk(game->s),game->s = NULL;
}
void cleanup(void)
{
     free_Game(getGame());
	 if(renderer)SDL_DestroyRenderer(getRenderer());
	 if(window)SDL_DestroyWindow(window);
	 Mix_CloseAudio();
	 IMG_Quit();
	 Mix_Quit();
	 TTF_Quit();
	 SDL_Quit();
}