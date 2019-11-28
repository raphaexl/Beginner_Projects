  
  #include "prototypes.h"
   int x = 0;
  int draw(void)
  {
if(SDL_RenderClear(getRenderer()))
  {
  	fprintf(stderr, " Erreur SDL_RenderClear() %s\n",SDL_GetError());
  	return -1;
  }
   if(drawGame()) return -1;
   SDL_RenderPresent(getRenderer());
   SDL_Delay(1);
   return 0;
  }



  int drawGame(void)
  {
    if(getGame()->level == 0)
    {
     if(drawImage(getGame()->menu,0,0))
      return -1;
    }
    else 
      {
        if(getGame()->level == 1)
    {
      getGame()->speed = -3;
     getEnemy()->speed = getGame()->speed;
    }
     
    else if(getGame()->level == 2)
    {
      getGame()->speed = -5;
     
      getEnemy()->speed = getGame()->speed;
    }

    else if(getGame()->level == 3)
    {
      getGame()->speed = -7;
      getEnemy()->speed = getGame()->speed;
    }
   
    if(scrollinBackground(getGame()->fond,0,getGame()->speed))return -1;
    if(drawImage(getPlayer()->bird1,getPlayer()->posO.x,getPlayer()->posO.y)) return -1;
    if(drawImage(getEnemy()->tuyau1,getEnemy()->posT1.x,getEnemy()->posT1.y)) return -1;
    if(drawImage(getEnemy()->tuyau2,getEnemy()->posT2.x,getEnemy()->posT2.y)) return -1;
   
  /*if(getGame()->play)*/
  }

   return 0;
  }
int scrollinBackground(SDL_Texture *texture,int xcord,int speed)
  {
    SDL_Rect pos = {xcord,0,140,400};
      /* Scrolling de La Route*/
     pos.x  =  negatModulo(x,pos.w) -  pos.w;
    if(drawImage(texture,pos.x,pos.y)) return -1;
     pos.x  =  negatModulo(x,pos.w);
    if(drawImage(texture,pos.x,pos.y)) return -1;
     pos.x  =  negatModulo(x,pos.w) + pos.w ;
    if(drawImage(texture,pos.x,pos.y)) return -1;
    /* pos.x  =  negatModulo(x,SCREEN_WIDTH) - SCREEN_WIDTH ;
    if(drawImage(texture,pos.x,pos.y)) return -1;*/

    x+=speed;
    return 0;
  }
 
int gamePlay(Input *in)
 {
  
  
  float factGravite = 0.5f;
 float factSautMaintenu = 3.0f;
 float impulsion = 6.0f;

 if(in->up){
  saute(impulsion);
   Mix_PlayChannel(0,getGame()->tab[0],0);
 }
  gravite(in,factGravite,factSautMaintenu);
  controllSol();
   getPlayer()->current = getPlayer()->bird1;
   getPlayer()->posO.y += getPlayer()->vy;
  /* Reglage des ENEMY */
 
   getEnemy()->posT1.x += getEnemy()->speed;
   getEnemy()->posT2.x += getEnemy()->speed;
   if(getEnemy()->posT1.x +getEnemy()->posT1.w <=0)
   {
    getEnemy()->posT1.x = randomNumber(280,285);
    getEnemy()->posT1.y = -randomNumber(100,200);
  
   getEnemy()->posT2.x =   getEnemy()->posT1.x ;
    getEnemy()->posT2.y =   (getEnemy()->posT1.y + getEnemy()->posT1.h)+120; 
    
   }

 if(collision(getPlayer()->posO,getEnemy()->posT1)||collision(getPlayer()->posO,getEnemy()->posT2))
    Mix_PlayChannel(0,getGame()->tab[1],0);
  if(getPlayer()->posO.x == (getEnemy()->posT1.x +getEnemy()->posT1.w))
  {
    Mix_PlayChannel(0,getGame()->tab[2],0);  
    getPlayer()->score +=1;
  }
 
  return 0;
 }

void saute(float impulsion)
{
  getPlayer()->vy = -impulsion;
  getPlayer()->current = getPlayer()->bird2;
}
void controllSol(void)
{
  if(getPlayer()->posO.y >330)
   {
    getPlayer()->posO.y = 330.0f;
    if(getPlayer()->vy>0)
      getPlayer()->vy = 0.0f;
  }
  if(getPlayer()->posO.y <0)
   {
    getPlayer()->posO.y = 0.0f;
    if(getPlayer()->vy>0)
      getPlayer()->vy = 0.0f;
  }
}
void gravite(Input *in,float factGravite, float factSautMaintenu)
{
   if(in->up)
    factGravite/=factSautMaintenu;
  getPlayer()->vy += factGravite;
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

int drawImage(SDL_Texture *texture,int x, int y)
{
  SDL_Rect pos;
  pos.x = x;
  pos.y = y;
   if(SDL_QueryTexture(texture,NULL,NULL,&pos.w,&pos.h))
   {
    fprintf(stderr, " Erreur SDL_QueryTexture() %s\n", SDL_GetError());
    return -1;
   }

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
