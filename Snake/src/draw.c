#include "prototypes.h"



int draw(Well *well,Serpent *sp)
{
	if(SDL_RenderClear(getRenderer()))
	{
		fprintf(stderr, "Erreur SDL_RenderClear() %s\n",SDL_GetError() );
		return -1;
	}
     
     if(serpent_move(sp))return -1;
    if(well_display(well,sp))return -1;
       if(serpent_display(sp))return -1;
         
    if(SDL_SetRenderDrawColor(getRenderer(),0,0,0,0xff))
	{
		fprintf(stderr, "Erreur SDL_SetRenderDrawColor() %s\n", SDL_GetError());
		return -1;
	}
   
    SDL_Delay(100);
    if(!sp->isAlive)
    {
    	init_serpent(sp);
    }
	SDL_RenderPresent(getRenderer());
	return 0;
}

int drawImage(SDL_Texture *image,int x, int y,SDL_Rect pos)
{
	SDL_Rect src = {x,y,pos.w,pos.h};
	if(SDL_RenderCopy(getRenderer(),image,&src,&pos))
	{
		fprintf(stderr, "Erreur SDL_RenderCopy() %s\n",SDL_GetError() );
		return -1;
	}
	return 0;
}

SDL_Texture *loadImage(char path[],int R,int G,int B)
{
	 SDL_Surface *surf = NULL;
	 surf = IMG_Load(path);
	 if(!surf)
	 {
	 	fprintf(stderr, "Erreur IMG_Load() %s\n",IMG_GetError() );
	 	return NULL;
	 }
	 if(SDL_SetColorKey(surf,SDL_TRUE,SDL_MapRGB(surf->format,R,G,B)))
	 {
	 	fprintf(stderr, "Erreur SDL_SetColorKey() %s\n", SDL_GetError());
	 	return NULL;
	 }

	 SDL_Texture *image = SDL_CreateTextureFromSurface(getRenderer(),surf);
	 if(!image)
	 {
	 	fprintf(stderr, "Erreur SDL_CreateTextureFromSurface() %s\n",SDL_GetError() );
	 	return NULL;
	 }
   SDL_FreeSurface(surf),surf = NULL;
   return image;
}

int setWindowColor(void)
{
	if(SDL_SetRenderDrawColor(getRenderer(),randomNumber(0,255),randomNumber(0,255),randomNumber(0,255),randomNumber(0,255)))
	{
		fprintf(stderr, "Erreur SDL_SetRenderDrawColor() %s\n",SDL_GetError() );
		return -1;
	}
	return 0;
}
int well_display(Well *well,Serpent *sp)
{
	(void)sp;
		if(setWindowColor())return -1;
	for (int i = 0; i < W; ++i)
	{
		for (int j = 0; j < H; ++j)
		{
			if(well->data[i][j])
			{
				SDL_Rect rect = {i*SCREEN_WIDTH/40 , j*SCREEN_WIDTH/40,SCREEN_WIDTH/40 ,SCREEN_WIDTH/40};
				SDL_RenderFillRect(getRenderer(),&rect);
			}	
			else 
			{
				SDL_RenderDrawPoint(getRenderer(),i*SIZE,j*SIZE);
			}
		}
	}

	return 0;
}

int new_apple(Serpent *sp)
{
	int  i ,j;
	do
	{
		i = rand()%W;
		j = rand()%H;
	}while(sp->grille[i][j]!=EMPTY);
	sp->grille[i][j] = APPLE;
	
	return 0;
}

int serpent_display(Serpent *sp)
{

  for (int i = 0; i < W; ++i)
   {
   for (int j = 0; j < H; ++j)
   {
    
    if(sp->grille[i][j]!=EMPTY)
    
     {
     	if(sp->grille[i][j] == SNAKE)
    {
    		SDL_Rect rect={i*SIZE+1,j*SIZE+1,SIZE-1,SIZE-1};
    	SDL_SetRenderDrawColor(getRenderer(),0xff,0x00,0x00,0xff);
       if(SDL_RenderFillRect(getRenderer(),&rect))
     	{
     		fprintf(stderr, "Erreur SDL_RenderFillRect() %s\n", SDL_GetError());
     		return -1;
     	}
   
    }
     else if(sp->grille[i][j] == APPLE)
    {
    		SDL_Rect rect={i*SIZE+1,j*SIZE+1,SIZE-1,SIZE-1};
    	SDL_SetRenderDrawColor(getRenderer(),0x00,0x00,0xff,0xff);
       if(SDL_RenderFillRect(getRenderer(),&rect))
     	{
     		fprintf(stderr, "Erreur SDL_RenderFillRect() %s\n", SDL_GetError());
     		return -1;
     	}
   
    }
     }
     

     	
   }
		}	

	return 0;
}

int serpent_move(Serpent *sp)
{
	
	static const Pos dir[4] = {{0,-1},{0,1},{1,0},{-1,0}};
	Pos hdPos = sp->pos[sp->hd];
	Pos tdPos = sp->pos[sp->td];

	if(!sp->grow)
	{
		sp->grille[tdPos.lig][tdPos.col] = EMPTY;
		
     sp->td = (sp->td+1)%(MAX_SIZE);

	}
	else
		sp->grow = false;
	
	sp->hd = (sp->hd +1)%(MAX_SIZE);

	hdPos.lig += dir[sp->_direction].lig;
	hdPos.col += dir[sp->_direction].col;
      sp->pos[sp->hd] = hdPos;

      if(snake_evolue(sp))
      {
             if(sp->grille[hdPos.lig][hdPos.col] == APPLE)
             {
             	sp->grow = true;
             	new_apple(sp);
             	
             }
             sp->grille[hdPos.lig][hdPos.col] = SNAKE;
      }
  else
      	sp->isAlive = false;
	 return 0;
}


   
    
bool snake_evolue(Serpent *sp)
{
	int x = sp->pos[sp->hd].lig;
	int y =  sp->pos[sp->hd].col;
	if(x>=0&&x<W&&y>0&&y<H&&(sp->grille[x][y]!=SNAKE))return true;

     return false;
}
