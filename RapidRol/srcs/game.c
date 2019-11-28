#include "prototypes.h"

void saute(Balle *balle,float impulsion)
{
	 balle->vy = -impulsion;
}

void gravite(Balle *balle,float factGravite,float factsautmaintenu,Input *in)
{
	 if(in->key[SDL_SCANCODE_SPACE])
	 	factGravite/=factsautmaintenu;
	 balle->vy += factGravite;
}
 int gamePlay(Context *C,Balle *balle,Input *in)
 {

 float lateralSpeed = 1.50f;
 float maxhspeed = 3.0f;
 float adherance = 1.5f;
 float impulsion = 6.0f;
 float factGravite = 0.50;
 float factsautmaintenu = 3.0f;


 	if(in->key[SDL_SCANCODE_RIGHT])
 		balle->vx+=lateralSpeed;
 	else if(in->key[SDL_SCANCODE_LEFT])
 		balle->vx-=lateralSpeed;
 	else if(!in->key[SDL_SCANCODE_RIGHT]&&!in->key[SDL_SCANCODE_LEFT])
 		balle->vx/=adherance;
    if(in->key[SDL_SCANCODE_SPACE])
    	saute(balle,impulsion);
       gravite(balle,factGravite,factsautmaintenu,in);
 	controll(C,balle);
 	if(balle->vx>maxhspeed)
 		balle->vx = maxhspeed;
 	if(balle->vx<-maxhspeed)
 		balle->vx = -maxhspeed;
   balle->pos.x += balle->vx;
   balle->pos.y += balle->vy;
 	
 	return 0;
 }

int controll(Context *C,Balle *balle)
{
	for(int i=0;i<5;++i)
	if(collision(C->pos[i],balle->pos))
	{
		if(balle->pos.x + balle->pos.w>=C->pos[i].x && balle->pos.x <=C->pos[i].x+C->pos[i].w)
			{
				balle->pos.y = C->pos[i].y - balle->pos.h;

				balle->vy = 0;
			}
	}
      else
		if(balle->pos.y+balle->pos.h<=0)
		{
			balle->pos.x = SCREEN_WIDTH/2;
			balle->pos.y = SCREEN_HEIGHT/2;
		}
		else
		if(balle->pos.x+balle->pos.w>=SCREEN_WIDTH) balle->vx *=-1;
	   else
		if(balle->pos.x<=0) balle->vx *=-1;
	    else if(balle->pos.y>=SCREEN_HEIGHT)
		{
			balle->pos.x = SCREEN_WIDTH/2;
			balle->pos.y = SCREEN_HEIGHT/2;
		}
	return 0;
}
