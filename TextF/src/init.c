#include "prototypes.h"


SDL_Window *window = NULL;
SDL_Renderer *renderer =  NULL;

SDL_Renderer *getRenderer(void)
{
	return renderer;
}
SDL_Window *getWindow(void)
{
  return window;
}

int init(char *title)
 {
    SDL_Surface *icone  = NULL;

    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO))
    {
    	fprintf(stderr, " Erreur SDL_Init() %s\n", SDL_GetError() );
    	return -1;
    }

    window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
    if(!window)
    {
    	fprintf(stderr, " Erreur SDL_CreateWindow() %s\n",SDL_GetError() );
    	return -1;
    }
     
     icone = SDL_LoadBMP("graphics/sdl_icone.bmp");
     if(!icone)
     {
     	fprintf(stderr, " Erreur SDL_LoadBMP() %s\n",SDL_GetError() );
     	return -1;
     }
     SDL_SetWindowIcon(window,icone);
     SDL_FreeSurface(icone),icone = NULL;
     renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
     if(!renderer)
     {
     	fprintf(stderr, " Erreur SDL_CreateRenderer() %s\n", SDL_GetError());
     	return -1;
     }

   if(Mix_Init(MIX_INIT_MP3))
   {
   	fprintf(stderr, " Erreur Mix_Init() %s\n",Mix_GetError() );
   	return -1;
   }
   if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024))
   {
   	fprintf(stderr, " Erreur Mix_openAudio() %s\n",Mix_GetError());
   	return -1;
   }
 
   if(!IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG))
   {
   	fprintf(stderr, " Erreur IMG_Init() %s\n", IMG_GetError());
   	return -1;
   }
     if(TTF_Init())
     {
     	fprintf(stderr, " Erreur TTF_Init() %s\n",TTF_GetError() );
     	return -1;
     }

     return 0;
 }

int init_Context(Context *C)
 {
  SDL_Color couleur1 = {0,0,0, 255}, couleur2 = {0,0,0, 255};
  SDL_Surface *mesTxt[11];
  char *all[] = {
        "Les Dix Commandements de Dieu .",
     "1- Tu aimeras Le Seigneur Ton Dieu de tout ton Coeur de toute ton ame et de toute tes forces.",
     "2- Je Suis Le Seigneur Ton Dieu.Tu n'auras pas d'autre dieux en face de moi.",
     "3- Tu ne prononceras pas Le Nom Du Seigneur Sans Respect .",
     "4- Tu respecteras le septieme, jour du Sabbat",
     "5- Tu honnorera Ton Pere et Ta mere ",
     "6- Tu ne tueras pas",
     "7- Tu ne commettras pas d'adultere.",
     "8- Tu ne commettras pas de rapt.",
     "9- Tu ne temoigneras pas faussement contre Ton prochain ",
     "10- Tu n'auras pas de visees sur ton prochain "
    
  };
   C->len = 11;
     for (int i = 0; i < C->len; ++i)
     {
      C->text[i]  = (char *) malloc(sizeof(char));
     }
   
    C->police1 = TTF_OpenFont("fonts/angelina.ttf",42);
    C->police2 = TTF_OpenFont("fonts/caslonBold.ttf",45);
   for (int i = 0; i < C->len; ++i)
   {
     C->text[i] = all[i];
   
   mesTxt[i] = TTF_RenderText_Shaded(C->police1,C->text[i],couleur1,couleur2);
   if(SDL_SetColorKey(mesTxt[i],SDL_TRUE,SDL_MapRGB(mesTxt[i]->format,couleur1.r,couleur1.g,couleur1.b)))
   {
    fprintf(stderr, " Erreur SDL_SetColorKey() %s\n", SDL_GetError());
    return -1;
   }
   C->message[i] = SDL_CreateTextureFromSurface(getRenderer(),mesTxt[i]);
   if(!C->message[i])
   {
    fprintf(stderr, "Erreur SDL_CreateTextureFromSurface() %s\n", SDL_GetError());
    return -1;
   }
   SDL_FreeSurface(mesTxt[i]),mesTxt[i] = NULL;
   if(SDL_QueryTexture(C->message[i],NULL,NULL,&C->pos[i].w,&C->pos[i].h))
   {
    fprintf(stderr, "Erreur SDL_QueryTexture() %s\n", SDL_GetError());
    return -1;
   }
   C->pos[i].x = 0;
   C->pos[i].y = 0;
 }
   return 0;
 }

void free_Context(Context *C)
{
  for (int i = 0; i < C->len; ++i)
  {
    if(C->message[i])SDL_DestroyTexture(C->message[i]),C->message[i] = NULL;
  }
 
  if(C->police1)TTF_CloseFont(C->police1),C->police1 = NULL;
  if(C->police2)TTF_CloseFont(C->police2),C->police2 = NULL;
}
 void cleanup(void)
 {
 	  if(window)SDL_DestroyWindow(window),window = NULL;
      if(renderer)SDL_DestroyRenderer(renderer),renderer =  NULL;
      Mix_CloseAudio();
      Mix_Quit();
      IMG_Quit();
      TTF_Quit();
      SDL_Quit();
 }
