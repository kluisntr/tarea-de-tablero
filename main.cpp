#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>

#include <iostream>

int vervox=1;
 int vervoy=1;

using namespace std;
int  posicion()
{
    return 0;
};

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
int tile_white=32;

int main()
{
     //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("juego de capo", 100, 100, 1248/*WIDTH*/, 544/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }
    SDL_Texture* texture_piso,*texture_pared,*texture_Malo,*texture_Cursor,*texture_Seleccionado;
    SDL_Rect Rectangulomalo1;
    SDL_Rect Rectangulopiso;
    SDL_Rect Rectangulomuro;
    SDL_Rect Rectangulocursor;
    texture_piso= IMG_LoadTexture(renderer,"piso.png");
    texture_pared= IMG_LoadTexture(renderer,"muro.png");
    texture_Malo= IMG_LoadTexture(renderer,"bueno1.png");
    texture_Cursor= IMG_LoadTexture(renderer,"cursor.png");
    texture_Seleccionado= IMG_LoadTexture(renderer,"seleccion.png");
    Rectangulomalo1.x=32;
    Rectangulomalo1.y=32;
    Rectangulomalo1.w=tile_white;
    Rectangulomalo1.h=tile_white;

 Rectangulomuro.x=0;
    Rectangulomuro.y=0;
    Rectangulomuro.w=tile_white;
    Rectangulomuro.h=tile_white;

 Rectangulopiso.x=0;
    Rectangulopiso.y=0;
    Rectangulopiso.w=tile_white;
    Rectangulopiso.h=tile_white;

    Rectangulocursor.x=tile_white;
    Rectangulocursor.y=0;
    Rectangulocursor.w=tile_white;
    Rectangulocursor.h=tile_white;

 int frame=0;
 int frame_actual=0;
 int frame_anterior=0;
 int cursor_x=1;
 int cursor_y=1;
 bool seleccion=false;
bool arro[17][39];
    int arr[17][39]={{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1},
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1},
                    {1,0,0,1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,1,1,1,0,1,1,1,1},
                    {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,1,1,0,1,1,1,1},
                    {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,1,1,1},
                    {1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,1},
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1},
                    {1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,1},
                    {1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,1,0,1,1,1,1,1,0,1,0,0,1,0,0,0,0,0,0,1,1},
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1},
                    {1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1,1},
                    {1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
                    {1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,1,0,0,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

                    for(int x=0;x<39;x++)
                        {
                            for(int y=0;y<17;y++)
                            {
                                    if(arr[y][x]==1){
                                        arro[y][x]==false;
                                        }else
                                         arro[y][x]==true;
                            }
                        }
//ciclo de movimiento


    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
        if(Event.type==SDL_QUIT)
            {
                return 0;

            }
            if(Event.type==SDL_KEYDOWN)

            {
            if(Event.key.keysym.sym==SDLK_w)
            {
            if(vervoy=2)
                {

                if(arr[cursor_y-1][cursor_x]!=1)
                cursor_y--;
                }
            }
            if(Event.key.keysym.sym==SDLK_s)
            {


                if(arr[cursor_y+1][cursor_x]!=1)
                cursor_y++;


            }

            if(Event.key.keysym.sym==SDLK_a)
            {

                if(arr[cursor_y][cursor_x-1]!=1)
                cursor_x--;
            }

            if(Event.key.keysym.sym==SDLK_d)
            {

                if(arr[cursor_y][cursor_x+1]!=1)
                cursor_x++;
            }
            if(Event.key.keysym.sym==SDLK_z)
            {


                   if(Rectangulomalo1.x==Rectangulocursor.x&&Rectangulomalo1.y==Rectangulocursor.y)
                    seleccion =true;

                         if(arr[cursor_y][cursor_x+1]!=1)
                         {

                         }


            }
             if(Event.key.keysym.sym==SDLK_x)
            {


                   if(Rectangulomalo1.x==Rectangulocursor.x&&Rectangulomalo1.y==Rectangulocursor.y)
                    seleccion =false;




            }

            }
        }



        for(int x=0;x<39;x++)
        {
            for(int y=0;y<17;y++)
            {
            if(arr[y][x]==1)
            {
            Rectangulomuro.x=x*tile_white;
            Rectangulomuro.y=y*tile_white;
            SDL_RenderCopy(renderer, texture_pared, NULL, &Rectangulomuro);
            }
            else
            {
            Rectangulopiso.x=x*tile_white;
            Rectangulopiso.y=y*tile_white;

            SDL_RenderCopy(renderer, texture_piso, NULL, &Rectangulopiso);
            }

            }
        }







        if(Event.key.keysym.sym==SDLK_SPACE)
            {
                    if(seleccion==true)
                    {
                    Rectangulomalo1.x=Rectangulocursor.x;
                    Rectangulomalo1.y=Rectangulocursor.y;
                    seleccion=false;
                    }




            }
        SDL_RenderCopy(renderer, texture_Malo, NULL, &Rectangulomalo1);

        Rectangulocursor.x=cursor_x*tile_white;
        Rectangulocursor.y=cursor_y*tile_white;
        SDL_RenderCopy(renderer, texture_Cursor, NULL, &Rectangulocursor);

            if(seleccion==true)
            {
            SDL_RenderCopy(renderer,texture_Seleccionado,NULL,&Rectangulomalo1 );
            }


// dibuja en la pantalla



                    SDL_RenderPresent(renderer);





        frame++;
        int frame_actual=SDL_GetTicks()-frame_anterior;
        frame_anterior=SDL_GetTicks();
        if(17-frame_actual>0)
        SDL_Delay(17-frame_actual);

    }



    return 0;
}
