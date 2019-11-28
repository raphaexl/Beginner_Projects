#ifndef DEFS_H
#define DEFS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>



#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define TICK_INTERVAL 20
#define PAD_MAX_SPEED  12.

#define BALL_MAX_SPEED 6.0
#define BALL_SPEED  8.0

#define BALL_START_VX  -1
#define BALL_START_VY  -0.5

#define COEF_DY 0.03
#define COEF_SPEED 0.1

#endif 
