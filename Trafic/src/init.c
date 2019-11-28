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

	 window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);
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
	game.level = 3;
	game.speed = 0;
   game.road[0] = loadImage("graphics/roadTrack.jpg");
   if(!game.road[0]) return -1;
   game.road[1] = loadImage("graphics/track.png");
   if(!game.road[1]) return -1;
   game.road[2] = loadImage("graphics/track2.png");
   if(!game.road[2]) return -1;
   game.menu = loadImage("graphics/menuracer.png");
   if(!game.menu) return -1; 
   
   /* Init Player */
   player.score = 0;
   player.car = loadImage("graphics/Audi.png");
   if(!player.car) return -1;
   player.pos.x = SCREEN_WIDTH/2;
   player.pos.y  =  SCREEN_HEIGHT - 218;

   /* Init Enemys*/
   enemy.pos1.x = 110;
   enemy.pos1.y  = 0;
   enemy.pos2.x  = 390;
   enemy.pos2.y  = 0;
   enemy.speed = 0;
   enemy.car1 = loadImage("graphics/Ambulance.png");
   if(!enemy.car1) return  -1;
   enemy.car2 = loadImage("graphics/Black_Viper.png");
   if(!enemy.car2) return -1;
   enemy.cars[0] = loadImage("graphics/Ambulance.png");
   enemy.cars[1] = loadImage("graphics/Black_Viper.png");
   enemy.cars[2] = loadImage("graphics/Car.png");
   enemy.cars[3] = loadImage("graphics/car2.png");
   enemy.cars[4] = loadImage("graphics/carGreen.png");
   enemy.cars[5] = loadImage("graphics/carGrey.png");
   enemy.cars[6] = loadImage("graphics/carYellow.png");
   enemy.cars[7] = loadImage("graphics/carOrange.png");
   enemy.cars[8] = loadImage("graphics/carPink.png");
   enemy.cars[9] = loadImage("graphics/carRed.png");
   enemy.cars[10] = loadImage("graphics/Mini_truck.png");
   enemy.cars[11] = loadImage("graphics/Mini_van.png");
   enemy.cars[12] = loadImage("graphics/police.png");
   enemy.cars[13] = loadImage("graphics/taxi.png");
   enemy.cars[14] = loadImage("graphics/truck.png");
   enemy.cars[15] = loadImage("graphics/truckBlue.png");
   enemy.cars[16] = loadImage("graphics/TruckWhite.png");
  
 for (int i = 0; i < 16; ++i)
 {
 if(!enemy.cars[i]) return -1;
 }
  
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
	 for(int i = 0; i<3;++i)
	 if(game->road[i])SDL_DestroyTexture(game->road[i]), game->road[i]= NULL;
     if(getPlayer()->car) SDL_DestroyTexture(getPlayer()->car);
     if(getEnemy()->car1)SDL_DestroyTexture(getEnemy()->car1);
     if(getEnemy()->car2)SDL_DestroyTexture(getEnemy()->car2);
     for (int i = 0; i < 16; ++i)
     {
     	if(getEnemy()->cars[i])SDL_DestroyTexture(getEnemy()->cars[i]);
     }
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