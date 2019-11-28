  
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
      SDL_Rect pos = {0,0,15,15};
     if(drawImage(getGame()->menu,pos))
      return -1;
    }
    else 
      {
        if(getGame()->level == 1)
    {
      getGame()->speed = 6;
      getGame()->track = getGame()->road[0];
     getEnemy()->speed = getGame()->speed;
    }
     
    else if(getGame()->level == 2)
    {
      getGame()->speed = 8;
      getGame()->track = getGame()->road[1];
      getEnemy()->speed = getGame()->speed;
    }

    else if(getGame()->level == 3)
    {
      getGame()->speed = 10;
      getGame()->track = getGame()->road[2];
      getEnemy()->speed = getGame()->speed;
    }
   
   if(scrollinBackground(getGame()->track,0,getGame()->speed))return -1;
    if(drawImage(getPlayer()->car,getPlayer()->pos)) return -1;
    if(drawImage(getEnemy()->car1,getEnemy()->pos1)) return -1;
    if(drawImage(getEnemy()->car2,getEnemy()->pos2)) return -1;
  }

   return 0;
  }
int scrollinBackground(SDL_Texture *texture,int xcord,int speed)
  {
    SDL_Rect pos = {xcord,0,0,0};
      /* Scrolling de La Route*/
     pos.y  =  negatModulo(x,SCREEN_HEIGHT);
    if(drawImage(texture,pos)) return -1;
     pos.y  =  negatModulo(x,SCREEN_HEIGHT) - SCREEN_HEIGHT ;
    if(drawImage(texture,pos)) return -1;
    x+=speed;
    return 0;
  }
 
 int gamePlay(Input *in)
 {
  if(getPlayer()->pos.x>=110 && getPlayer()->pos.x<=342)
  {
   if(in->right) getPlayer()->pos.x +=getGame()->speed;
   if(in->left) getPlayer()->pos.x -=getGame()->speed;
   if(in->up) getPlayer()->pos.y -= getGame()->speed;
   if(in->down) getPlayer()->pos.y +=getGame()->speed;
  }
  else if(getPlayer()->pos.x<110)getPlayer()->pos.x = 110;
  else if(getPlayer()->pos.x>342)getPlayer()->pos.x = 342;


  /* Reglage des ENEMY */
   
   getEnemy()->pos1.y += getEnemy()->speed;
   if(getEnemy()->pos1.y >=SCREEN_HEIGHT)
   {
    getEnemy()->pos1.x = randomNumber(110,200);
    getEnemy()->pos1.y = -randomNumber(0,150);
     if(getEnemy()->pos1.x <110 ||collision(getEnemy()->pos1 ,getEnemy()->pos2))
    getEnemy()->pos1.x = randomNumber(342,110);
   
    getEnemy()->car1 = getEnemy()->cars[randomNumber(0,16)];
   }
    
  getEnemy()->pos2.y += getEnemy()->speed;
   if(getEnemy()->pos2.y >=SCREEN_HEIGHT)
   {
    getEnemy()->pos2.x = randomNumber(200,31);
    getEnemy()->pos2.y = -randomNumber(0,150);
     if(getEnemy()->pos2.x >342||collision(getEnemy()->pos1 ,getEnemy()->pos2))
    getEnemy()->pos2.x = randomNumber(200,342);
    getEnemy()->car2 = getEnemy()->cars[randomNumber(0,16)];
   }

  
  return 0;
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

int drawImage(SDL_Texture *texture,SDL_Rect dest)
{
  SDL_Rect pos;
  pos.x = dest.x;
  pos.y = dest.y;
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