  
  #include "prototypes.h"
   int x = 0;
  int frameTime = 0;
    int draw(Game *game,Player *player)
  {
if(SDL_RenderClear(getRenderer()))
  {
  	fprintf(stderr, " Erreur SDL_RenderClear() %s\n",SDL_GetError());
  	return -1;
  }
   if(drawGame(game,player)) return -1;

   SDL_RenderPresent(getRenderer());
   SDL_Delay(1);
   return 0;
  }

int drawPlayer(Player *player)
{
  frameTime++;
if(FPS/frameTime == 12)
{
 player->src.x += player->frameWidth;
  frameTime = 0;
}
 if(player->src.x >= 7*player->frameWidth)
 player->src.x = 0;

   if(SDL_RenderCopy(getRenderer(),player->image,&player->src,&player->dest))
   {
    fprintf(stderr, " Erreur SDL_RenderCopy() %s\n", SDL_GetError());
    return -1;
   }
    
   return 0;
}
  int drawGame(Game *game,Player *player)
  {
    if(game->level == 0)
    {
      SDL_Rect pos={0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
     if(drawImage(game->menu,pos))
      return -1;
    }
    else 
      {
        if(game->level == 1)
    {
      game->speed =  -5;
   // game->speed = game->speed;
    }
     
    else if(game->level == 2)
    {
      game->speed = -10;
     
     // game->speed = game->speed;
    }

    else if(game->level == 3)
    {
      game->speed = -15;
     // game->speed = getGame()->speed;
    }
   
   if(collision(player->dest,game->posT2)||collision(player->dest,game->posT1))
  game->speed = 1;

    if(scrollinBackground(game->fond,0,game->speed))return -1;
    if(drawPlayer(player)) return -1;
    if(drawImage(game->tuyau1,game->posT1)) return -1;
    if(drawImage(game->tuyau2,game->posT2)) return -1;

  }

   return 0;
  }
int scrollinBackground(SDL_Texture *texture,int xcord,int speed)
  {
    SDL_Rect pos = {xcord,0,800,SCREEN_HEIGHT};
      /* Scrolling de La Route*/
     pos.x  =  negatModulo(x,pos.w) -  pos.w;
    if(drawImage(texture,pos)) return -1;
     pos.x  =  negatModulo(x,pos.w);
    if(drawImage(texture,pos)) return -1;
     pos.x  =  negatModulo(x,pos.w) + pos.w ;
    if(drawImage(texture,pos)) return -1;
    /* pos.x  =  negatModulo(x,SCREEN_WIDTH) - SCREEN_WIDTH ;
    if(drawImage(texture,pos.x,pos.y)) return -1;*/

    x+=speed;
    return 0;
  }
 
int gamePlay(Input *in,Game *game,Player *player)
 {
  
  
  float factGravite = 0.5f;
 float factSautMaintenu = 3.0f;
 float impulsion = 11.0f;

 if(in->up)saute(impulsion,player);

  gravite(in,factGravite,factSautMaintenu,player);
  controllSol(player);
   player->dest.y += player->vy;
  /* Reglage des ENEMY */
 
    game->posT1.x += game->speed;
    game->posT2.x += game->speed;
   if(game->posT1.x +game->posT1.w <0)
   {
    game->posT1.x = randomNumber(800,805);
    game->posT1.y = randomNumber(200,300);
    
   }
    if(game->posT2.x +game->posT2.w <0)
   {
    game->posT2.x = 120+ randomNumber(800,805);
     game->posT2.y = randomNumber(200,300);
    
   }


  return 0;
 }

void saute(float impulsion,Player *player)
{
  player->vy = -impulsion;
  
}
void controllSol(Player *player)
{
  if(player->dest.y >350)
   {
    player->dest.y = 350.0f;
    if(player->vy>0)
      player->vy = 0.0f;
  }
  if(player->dest.y <0)
   {
    player->dest.y = 0.0f;
    if(player->vy>0)
     player->vy = 0.0f;
  }
}
void gravite(Input *in,float factGravite, float factSautMaintenu,Player *player)
{
   if(in->up)
    factGravite/=factSautMaintenu;
  player->vy += factGravite;
}

  SDL_Texture *loadImage(char path[])
  {
  	SDL_Surface *surf = NULL;
  	SDL_Texture *image = NULL;
  	surf = IMG_Load(path);
  	 if(!surf)
  	 {
  	 	fprintf(stderr, " Erreur IMG_Load() %s\n", IMG_GetError());
  	 	return NULL;
  	 }
  	 if(SDL_SetColorKey(surf,SDL_TRUE,SDL_MapRGB(surf->format,255,255,255)))
  	 {
  	 	fprintf(stderr, " Erreur SDL_SetColorKey() %s\n",SDL_GetError() );
  	 	return NULL;
  	 }
    image = SDL_CreateTextureFromSurface(getRenderer(),surf);
     if(!image)
     {
     	fprintf(stderr, " Erreur SDL_CreateTextureFromSurface() %s\n", SDL_GetError());
     	return NULL;
     }
   
     SDL_FreeSurface(surf),surf = NULL;

   return image;
  }

int drawImage(SDL_Texture *texture, SDL_Rect pos)
{
 
   if(SDL_RenderCopy(getRenderer(),texture,NULL,&pos))
   {
    fprintf(stderr, " Erreur SDL_RenderCopy() %s\n", SDL_GetError());
    return -1;
   }
   return 0;
}

void delay(unsigned int frameLimit )
 {
   unsigned int ticks = SDL_GetTicks();
   if(frameLimit <ticks)
    return;
  else if(frameLimit>ticks+16)
    SDL_Delay(16);
  else
    SDL_Delay(frameLimit-ticks);
 }
