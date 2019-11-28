#ifndef DEFS_H
#define DEFS_H

   #include<stdio.h>
   #include<stdlib.h>
   #include<math.h>
   #include<stdbool.h> 
   #include<time.h>


   #include <SDL2/SDL.h>
   #include <SDL2/SDL_image.h>
   #include <SDL2/SDL_mixer.h>
   #include <SDL2/SDL_ttf.h>



  #define SCREEN_WIDTH 1200
  #define SCREEN_HEIGHT 720
  #define W 60
  #define  H 36
  #define SIZE 20
  #define MAX_SIZE W*H

enum {width = 20,height = 20};
enum {EMPTY,SNAKE,APPLE};
enum  {UP,DOWN,RIGHT,LEFT};



#endif