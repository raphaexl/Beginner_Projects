 
 #include "prototypes.h"
 
 void paddle_slow_down(Paddle *paddle)
 {
   paddle->speed = (paddle->speed>0)?-1:1;
 }

 void balle_ensure_speed(Balle *balle)
 {
 	double speed = balle->coeff*sqrt(balle->vx*balle->vx + balle->vy*balle->vy);
 	balle->coeff *= BALL_SPEED/speed;
 }

 void paddle_update(Paddle *paddle,Context *C)
 {
 	 if(paddle->speed > PAD_MAX_SPEED)
 	 	paddle->speed = PAD_MAX_SPEED;
 	 if(paddle->speed<-PAD_MAX_SPEED)
 	 	paddle->speed = -PAD_MAX_SPEED;
 	 paddle->pos.y += paddle->speed;

 	 if(paddle->pos.y<20)
 	 	{
 	 		paddle->pos.y = 20;
 	 		paddle->speed = 0;
 	 	}
 	 	if(paddle->pos.y + paddle->pos.h > C->h -20)
 	 	{
 	 	paddle->pos.y = C->h -20 - paddle->pos.h;
 	 	paddle->speed = 0;	
 	 	}

 }

 void game_play(Context *C, Balle *balle,Paddle *paddle1,Paddle *paddle2,Input *in)
 {
    if(in->key[SDL_SCANCODE_DOWN])paddle1->speed++;
   else if(in->key[SDL_SCANCODE_UP])paddle1->speed--;
    else if(in->key[SDL_SCANCODE_Z])paddle2->speed++;
    else if(in->key[SDL_SCANCODE_W])paddle2->speed--;
    else;

    paddle_update(paddle1,C);
    paddle_update(paddle2,C);
    game_update(balle,paddle1,C);
    game_update(balle,paddle2,C);
 }


 void game_update(Balle *balle,Paddle *paddle,Context *C)
 {
    balle->pos.x += balle->vx*balle->coeff;
    balle->pos.y += balle->vy*balle->coeff;
    if(balle->pos.y<5)
    {
    	balle->pos.y = 5;
    balle->vy = -balle->vy;
    }
    else if(balle->pos.y+balle->pos.h>C->h -20)
    {
    	balle->pos.y = C->h -20 - balle->pos.h;
    balle->vy = -balle->vy;
    }

    else if(balle->pos.x<5)
    {
       balle->pos.x = C->w/2 - balle->pos.w/2;
       balle->pos.y = C->h/2 - balle->pos.h/2;
    }
   
    else if(balle->pos.x + balle->pos.w>C->w-20)
    {
       balle->pos.x = C->w/2 - balle->pos.w/2;
       balle->pos.y = C->h/2 - balle->pos.h/2;
    }

    else if(collision(balle->pos,paddle->pos))
    {
    	double dy = paddle->pos.y + paddle->pos.h/2 - balle->pos.y;
    	balle->vx *=-1;
    	balle->vy = -dy*COEF_DY + paddle->speed*COEF_SPEED;

    	if(balle->vy >BALL_MAX_SPEED)
    		balle->vy = BALL_SPEED;
    	if(balle->vy <-BALL_MAX_SPEED)
    		balle->vy = -BALL_MAX_SPEED;
    	balle_ensure_speed(balle);
    	balle->pos.x = paddle->pos.x - balle->pos.w;
    }
    else;
 }
 
 