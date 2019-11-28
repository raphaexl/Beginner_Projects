#include "prototypes.h"

void ensure_balle_speed(Balle *balle)
{
	 double speed = balle->coeff*sqrt(balle->vx*balle->vx + balle->vy*balle->vy);
	 balle->coeff *= BALL_SPEED/speed;

}

void slow_paddle_down(Paddle *paddle)
{
	paddle->speed = paddle->speed>0?-1:1;
}

void update_paddle(Context *C,Paddle *paddle)
{
	 if(paddle->speed>PAD_MAX_SPEED)
	 	paddle->speed = PAD_MAX_SPEED;
	 if(paddle->speed<-PAD_MAX_SPEED)
	   paddle->speed = -PAD_MAX_SPEED;

	paddle->pos.x += paddle->speed;

	if(paddle->pos.x + paddle->pos.w>C->w -16)
	{
        paddle->pos.x = C->w - 16 -paddle->pos.w;
        paddle->speed = 0;
	}

	if(paddle->pos.x < 16)
	{
		paddle->pos.x = 16;
		paddle->speed = 0;
	}
	paddle->pos.y = C->h - paddle->pos.h;

}

void gamePlay(Context *C,Balle *balle,Paddle *paddle,Input *in)
{
	SDL_GetWindowSize(getWindow(),&C->w,&C->h);
	 if(in->key[SDL_SCANCODE_RIGHT])paddle->speed++;
	 else if(in->key[SDL_SCANCODE_LEFT])paddle->speed--;
     else if(paddle->speed)slow_paddle_down(paddle);
    update_paddle(C,paddle);
    update_balle(C,balle,paddle);
    
}
void update_balle(Context *C,Balle *balle,Paddle *paddle)
{
	  balle->pos.x += balle->vx*balle->coeff;
	  balle->pos.y += balle->vy*balle->coeff;

	  if(balle->pos.x<16)
	  {
	  	balle->pos.x = 16;
	  	balle->vx *=-1;
	  	 Mix_PlayChannel(0,C->sd2,0);
	  }
	  else if(balle->pos.x>C->w-16-balle->pos.w)
	  {
	  	balle->pos.x = C->w-balle->pos.w-16;
	  	balle->vx *=-1;
	  	 Mix_PlayChannel(0,C->sd2,0);
	  }
	  else if(balle->pos.y<16)
	  {
	  	balle->pos.y = 16;
	  	balle->vy *=-1;
	  	 Mix_PlayChannel(0,C->sd2,0);
	  }
	  else if(collision(balle->pos,paddle->pos))
	  {
	  	 double dx = paddle->pos.x + paddle->pos.w/2 - balle->pos.x;
	  	 balle->vy *= -1;
	  	 balle->vx = dx*COEFF_DX + paddle->speed*COEFF_SPEED;
	  	 if(balle->vx>BALL_MAX_SPEED)
	  	 	balle->vx = BALL_MAX_SPEED;
	  	 if(balle->vx<-BALL_MAX_SPEED)
	  	 	balle->vx = -BALL_MAX_SPEED;
	  	 ensure_balle_speed(balle);
	  	 balle->pos.y = paddle->pos.y -balle->pos.h;
	  	 Mix_PlayChannel(0,C->sd3,0);
	  }
	  else if(balle->pos.y>C->h -16-balle->pos.h)
	  {
	  	balle->pos.x = C->w/2;
	  	balle->pos.y =C->h/2;
	  	 Mix_PlayChannel(0,C->sd4,0);
	  }
	  else 
	  {
	  	C->pos.w =  64;
 	C->pos.h = 24;
 	
 	 for (int i = 0; i < C->h/100; ++i)
 	 {
 	 	C->pos.y = i*24.5;
 	 	for(int j=0;j< C->w/64;++j)
 	 	{
 	 		C->pos.x = 16+ j*64;
 	 		if(C->grille[i][j]==1)
 	 		{
 	 			if(collision(balle->pos,C->pos))
 	 				
 	 				{
 	 					ensure_balle_speed(balle);
 	 	             
				     if(balle->pos.y<C->pos.y+C->pos.h)
				    {
                      balle->pos.y=C->pos.y+C->pos.h;
                      balle->vy *=-1;
                       if(balle->vx>BALL_MAX_SPEED)
				  	 	balle->vx = BALL_MAX_SPEED;
				  	 if(balle->vx<-BALL_MAX_SPEED)
				  	 	balle->vx = -BALL_MAX_SPEED;
                      C->grille[i][j] = 0;
                      SDL_Color color = {randomNumber(0,255),randomNumber(0,255),randomNumber(0,255),randomNumber(0,255)};
                      SDL_SetWindowColor(color);
				    }
				    Mix_PlayChannel(0,C->sd1,0);
 	 					ensure_balle_speed(balle);
 	 					
 	 				}
 	 		}
 	 		
 	    	}
 	 }
	  }
	  
	  	

}
