#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

void jouer(SDL_Surface *x);
int mario_gagne(SDL_Surface *x);
int colli_haut (SDL_Rect a , SDL_Rect T[])
 {
     int j;
     for(j=0;j<3;j++)
     {
     if ((a.y+a.h>=T[j].y) && (a.x+a.w>=T[j].x)&&(a.x+a.w<=T[j].x+T[j].w) )
 return (1);
     }
return (0);
}

int colli_droite (SDL_Rect a , SDL_Rect T[])
 { int j;
     for(j=0;j<3;j++)
     {
     if (((a.x+a.w)-1)==T[j].x )
 return (1);
     }
return (0);
}
int colli_gauche (SDL_Rect a , SDL_Rect T[])
 {
     int j;
     for(j=0;j<3;j++)
     {
          if (a.x==T[j].x+T[j].w )
 return (1);
     }

return (0);
}
int main(int argc, char *argv[])
{
    SDL_Surface *Ecran = NULL, *Menu = NULL ;
    SDL_Rect positionMenu,positionPanorama;
    SDL_Event event;
    int continuer = 1;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetIcon(IMG_Load("icone.bmp"), NULL);
    Ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Super Mario ", NULL);
    Menu = IMG_Load("menu.bmp");
    positionMenu.x = 0;
    positionMenu.y = 0;
    while (continuer)
      {
           SDL_WaitEvent(&event);
               switch(event.type)
                   {
                       case SDL_QUIT:
                            continuer = 0;
                            break;

                       case SDL_MOUSEBUTTONDOWN:
                           {
                               if(event.button.button == SDL_BUTTON_LEFT)
                                    {
                                         if((event.button.y>392)&&(event.button.y<432)&&(event.button.x>242)&&(event.button.x<761))
                                          continuer=0;
                                         else if ((event.button.y>330)&&(event.button.y<370)&&(event.button.x>242)&&(event.button.x<458))
                                            {
                                                jouer(Ecran);
                                            }
                                    }
                           }
                           break;
                        case SDL_KEYDOWN:
                                        switch(event.key.keysym.sym)
                                            {
                                                case SDLK_ESCAPE:
                                                continuer=0;
                                                break;
                                            }
                   }

                    SDL_FillRect(Ecran, NULL, SDL_MapRGB(Ecran->format, 0, 470, 0));
                    SDL_BlitSurface(Menu, NULL, Ecran, &positionMenu);
                    SDL_Flip(Ecran);
     }

    SDL_FreeSurface(Menu);
    SDL_Quit();

    return EXIT_SUCCESS;
}


//lorsque mario arrive à la princesse
int mario_gagne(SDL_Surface *Ecran)
{
    SDL_Surface *mariage;
    SDL_Rect position_mariage;
    position_mariage.x=0;
    position_mariage.y=0;
    mariage  = IMG_Load("mario_princesse.png");
                    SDL_Delay(2000);
                    SDL_FillRect(Ecran, NULL, SDL_MapRGB(Ecran->format, 0, 0, 0));
                    SDL_BlitSurface(mariage, NULL, Ecran, &position_mariage);
                    SDL_Flip(Ecran);
                    SDL_Delay(8000);
                   return 0;
}


void jouer(SDL_Surface *Ecran)
{   int continuer=1;
    SDL_Surface *MarioActuel=NULL, *Panorama=NULL;
    SDL_Surface *Mario[9] = {NULL};
    SDL_Rect positionMario,positionPanorama,positionActuel={0,0,32,60},posMarioRel,pos,T[3],camera = { 0, 0, 800, 600 };
    SDL_Event event,event_aux;
    Mario[1] = IMG_Load("images/mario0.png");
    Mario[2] = IMG_Load("images/mario1.png");
    Mario[3] = IMG_Load("images/mario2.png");
    Mario[4] = IMG_Load("images/mario_bas.png");
    Mario[5] = IMG_Load("images/mario3.png");
    Mario[6] = IMG_Load("images/mario4.png");
    Mario[7] = IMG_Load("images/mario5.png");
    Mario[8] = IMG_Load("images/mario_bas_gauche.png");
    Mario[9] = IMG_Load("images/mario_mort.png");
    MarioActuel = Mario[1];
    Panorama = IMG_Load("panorama.bmp");
    T[0]={1303,442,310,88};
    T[1]={5944,442,195,88};
    T[2]={6320,464,130,66};
    posMarioRel.x = -60;
    positionMario.x = 100;
    positionMario.y = 470;
    positionActuel.x=positionMario.x;
    positionActuel.y=positionMario.y;
    positionPanorama.x = 0;
    positionPanorama.y = 0;
    SDL_EnableKeyRepeat(1, 1);
    SDL_SetColorKey(MarioActuel, SDL_SRCCOLORKEY, SDL_MapRGB(MarioActuel->format, 255, 255, 255));
    int j,i=1,k,sol;
while(continuer)
{
                SDL_PollEvent(&event);
                        switch(event.type)
                            {
                                    case SDL_QUIT:
                                        continuer = 0;
                                    break;
                                    case SDL_KEYDOWN:
                                        switch(event.key.keysym.sym)
                                            {

                                                    case SDLK_UP: // Flèche haut/////////////////////////////////////////////////////////////////
                                                   {pos.x=positionMario.x ;
                                                    pos.y=positionMario.y ;
                                                    if(event_aux.key.keysym.sym==SDLK_RIGHT)
                                                    {
                                                       do
                                                       {    posMarioRel.x++;

                                                            posMarioRel.y=(-0.0277*(posMarioRel.x*posMarioRel.x)+140);
                                                            if(positionMario.x<400)
                                                            positionMario.x = pos.x + posMarioRel.x+60;
                                                            else
                                                            camera.x++;
                                                            positionMario.y = pos.y - posMarioRel.y;
                                                            SDL_FillRect(Ecran, NULL, SDL_MapRGB(Ecran->format, 0, 0, 0));
                                                            SDL_BlitSurface(Panorama, &camera, Ecran, NULL);
                                                            SDL_BlitSurface(MarioActuel, NULL, Ecran, &positionMario);
                                                            SDL_Flip(Ecran);
                                                            SDL_Delay(5);
                                                             positionActuel.x++;
                                                             positionActuel.y=positionMario.y;


                                                       }
                                while(positionMario.y<470 && !colli_haut(positionActuel,T));
                                                        posMarioRel.x = -60;
                                                        posMarioRel.y = 0;
                                                    }
                                                    else if(event_aux.key.keysym.sym==SDLK_LEFT)

                                                     {
                                                          do
                                                       {    posMarioRel.x++;

                                                            posMarioRel.y=(-0.0277*(posMarioRel.x*posMarioRel.x)+140);
                                                            if(positionMario.x>0)
                                                            positionMario.x = pos.x - posMarioRel.x-60;
                                                            else
                                                            camera.x--;
                                                            positionMario.y = pos.y - posMarioRel.y;
                                                            SDL_FillRect(Ecran, NULL, SDL_MapRGB(Ecran->format, 0, 0, 0));
                                                            SDL_BlitSurface(Panorama, &camera, Ecran, NULL);
                                                            SDL_BlitSurface(MarioActuel, NULL, Ecran, &positionMario);
                                                            SDL_Flip(Ecran);
                                                            SDL_Delay(5);
                                                            positionActuel.x--;
                                                            positionActuel.y=positionMario.y;
                                                       }
                                while(positionMario.y<470 && !colli_haut(positionActuel,T));


                                                        posMarioRel.x = -60;
                                                        posMarioRel.y = 0;
                                                     }
                                                     else
                                                     {for(k=0;k<140;k++)
                                                      {
                                                          positionMario.y--;
                                                          positionActuel.y--;
                                                          SDL_FillRect(Ecran, NULL, SDL_MapRGB(Ecran->format, 0, 0, 0));
                                                            SDL_BlitSurface(Panorama, &camera, Ecran, NULL);
                                                            SDL_BlitSurface(MarioActuel, NULL, Ecran, &positionMario);
                                                            SDL_Flip(Ecran);
                                                            SDL_Delay(1);
                                                      }
                                                      for(k=0;k<140;k++)
                                                      {
                                                          positionMario.y++;
                                                          positionActuel.y++;
                                                          SDL_FillRect(Ecran, NULL, SDL_MapRGB(Ecran->format, 0, 0, 0));
                                                            SDL_BlitSurface(Panorama, &camera, Ecran, NULL);
                                                            SDL_BlitSurface(MarioActuel, NULL, Ecran, &positionMario);
                                                            SDL_Flip(Ecran);
                                                            SDL_Delay(2);
                                                      }
                                                     }

                                                   }

                                                    event_aux.key.keysym.sym=SDLK_UP;
                                                break;
                                                case SDLK_DOWN: // Flèche bas
                                                if(i<4)
                                                    MarioActuel=Mario[4];
                                                else
                                                    MarioActuel=Mario[8];
                                                     event_aux.key.keysym.sym=SDLK_DOWN;
                                                break;
                                                case SDLK_RIGHT: // Flèche droite
                                                    {
                                                        if(i<3)
                                                        {
                                                            i++;
                                                        }
                                                        else if(i>=3)
                                                        {i=1;}
     if(((positionActuel.x==(T[0].x+T[0].w))&&(positionActuel.y<T[0].y))||((positionActuel.x==(T[1].x+T[1].w))&&(positionActuel.y<T[1].y))||((positionActuel.x==(T[2].x+T[2].w))&&(positionActuel.y<T[2].y)))
        {
            for(k=0;positionActuel.y!=470;k++)
            {positionActuel.y++;
            positionMario.y++;
                         SDL_FillRect(Ecran, NULL, SDL_MapRGB(Ecran->format, 0, 0, 0));
                         SDL_BlitSurface(Panorama, &camera, Ecran, NULL);
                         SDL_BlitSurface(MarioActuel, NULL, Ecran, &positionMario);
                         SDL_Flip(Ecran);
                         SDL_Delay(3);
            }

        }

                                                        MarioActuel=Mario[i];
                                                        if(!colli_droite(positionActuel,T))
                                                        {
                                                        if(positionMario.x>=400)
                                                        {
                                                                 camera.x+=1;
                                                                 positionActuel.x+=1;
                                                                 SDL_Delay(2);

                                                         }

                                                        else
                                                       {
                                                          positionMario.x+=1;
                                                          positionActuel.x+=1;
                                                          SDL_Delay(2);

                                                        }
                                                    }
                                                    }



                                                     event_aux.key.keysym.sym=SDLK_RIGHT;
                                                break;
                                                case SDLK_LEFT: // Flèche gauche
                                                {   if((i==5)||(i==6))
                                                        {
                                                            i++;
                                                        }
                                                    else if(i==7)
                                                        {i=5;}
                                                    else if(i<4)
                                                        i=5;
if(((positionActuel.x+positionMario.w+1==T[0].x -1)&&(positionActuel.y<T[0].y))||((positionActuel.x+positionMario.w+1==T[1].x -1)&&(positionActuel.y<T[1].y))||((positionActuel.x+positionMario.w+1==T[2].x -1)&&(positionActuel.y<T[2].y)))
        {
            for(k=0;positionActuel.y!=470;k++)
            {positionActuel.y++;
            positionMario.y++;
                         SDL_FillRect(Ecran, NULL, SDL_MapRGB(Ecran->format, 0, 0, 0));
                         SDL_BlitSurface(Panorama, &camera, Ecran, NULL);
                         SDL_BlitSurface(MarioActuel, NULL, Ecran, &positionMario);
                         SDL_Flip(Ecran);
                         SDL_Delay(3);
            }

        }

                                                    MarioActuel=Mario[i];
                                                    if(!colli_gauche(positionActuel,T))
                                                        {
                                                        if(positionMario.x>0)
                                                        {
                                                          positionMario.x-=1;
                                                          positionActuel.x-=1;
                                                          SDL_Delay(2);

                                                        }

                                                        else if(positionMario.x==0)
                                                       {if(positionActuel.x>0)
                                                         {
                                                          camera.x-=1;
                                                          positionActuel.x-=1;
                                                          SDL_Delay(2);
                                                         }
                                                       }
                                                        }
                                                }
                                                 event_aux.key.keysym.sym=SDLK_LEFT;
                                                break;

                                                case SDLK_ESCAPE:
                                                continuer=0;
                                                break;
                                            }
                                    break;
                                 case SDL_KEYUP:
                                        switch(event.key.keysym.sym)
                                            {    case SDLK_UP:
                                                         event_aux.key.keysym.sym=SDLK_UP;
                                                break;

                                                case SDLK_DOWN: // Flèche bas
                                                {if(i<4)
                                                    MarioActuel=Mario[1];
                                                else
                                                    MarioActuel=Mario[5];
                                                }
                                                 event_aux.key.keysym.sym=SDLK_DOWN;
                                                break;
                                                case SDLK_RIGHT: // Flèche droite

                                                        MarioActuel=Mario[1];
                                                         event_aux.key.keysym.sym=SDLK_DOWN;
                                                break;
                                                 case SDLK_LEFT: // Flèche gauche

                                                        MarioActuel=Mario[5];
                                                         event_aux.key.keysym.sym=SDLK_DOWN;
                                                break;

                                            }
                                    break;

                            }
if((((positionActuel.x>=2237)&&(positionActuel.x<=2344))||((positionActuel.x>=2985)&&(positionActuel.x<=2996))||((positionActuel.x>=3733)&&(positionActuel.x<=3740))||((positionActuel.x>=4701)&&(positionActuel.x<=4714))||((positionActuel.x>=5031)&&(positionActuel.x<=5042)))&&(positionActuel.y>=470))
                {MarioActuel=Mario[9];
                    for(j=0;j<90;j++)
                    {
                         positionMario.y--;
                         SDL_FillRect(Ecran, NULL, SDL_MapRGB(Ecran->format, 0, 0, 0));
                         SDL_BlitSurface(Panorama, &camera, Ecran, NULL);
                         SDL_BlitSurface(MarioActuel, NULL, Ecran, &positionMario);
                         SDL_Flip(Ecran);
                         SDL_Delay(4);

                     }

                     for(j=0;j<180;j++)
                     {
                         positionMario.y++;
                         SDL_FillRect(Ecran, NULL, SDL_MapRGB(Ecran->format, 0, 0, 0));
                         SDL_BlitSurface(Panorama, &camera, Ecran, NULL);
                         SDL_BlitSurface(MarioActuel, NULL, Ecran, &positionMario);
                         SDL_Flip(Ecran);
                         SDL_Delay(4);

                     }

                     SDL_Delay(500);

                     continuer=0;

                }
                if(positionActuel.x==6670)
                {
                    continuer=mario_gagne(Ecran);
                }

                SDL_FillRect(Ecran, NULL, SDL_MapRGB(Ecran->format, 0, 0, 0));
                SDL_BlitSurface(Panorama, &camera, Ecran, NULL);

                SDL_BlitSurface(MarioActuel, NULL, Ecran, &positionMario);
                SDL_Flip(Ecran);

}
}



