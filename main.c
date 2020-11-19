#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "fichier_SDL.h"
#include "initData.h"

void exceed_limit_right(sprite_t *ship){
    if ((ship->pos.x + 82/2) > 600-(82/2) ){
        ship->pos.x= 600 - (82);
    }
}

void exceed_limit_up(sprite_t *ship){
    if ((ship->pos.y) < 0 ){
        ship->pos.y = 0;
    }
}


void exceed_limit_left(sprite_t *ship){
    if ((ship->pos.x - 82/2) < 0 - (82/2) ){
        ship->pos.x = 0;
    }
}

void exceed_limit_down(sprite_t *ship){
    if ((ship->pos.y) > 600 - 82 ){
        ship->pos.y = 600 - 82;
    }
}


int main(int argc, char *argv[]){

    SDL_Window* fenetre;  // Déclaration de la fenêtre
    SDL_Event evenements; // Événements liés à la fenêtre

    bool terminer = false;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) // Initialisation de la SDL
    {
        printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    // Créer la fenêtre
    fenetre = SDL_CreateWindow("Warblade Like", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 600, 600, 0);
    if(fenetre == NULL) // En cas d’erreur
    {
        printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Mettre en place un contexte de rendu de l’écran
    SDL_Renderer* ecran;
    ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    // Charger l’image
    SDL_Texture* fond = charger_image( "images/fond.bmp", ecran );

    world_t world = initData(ecran);

    SDL_Rect SrcR;
    SrcR.w = 82; // Largeur de l’objet en pixels (à récupérer)
    SrcR.h = 82; // Hauteur de l’objet en pixels (à récupérer)
    
    // Boucle principale
    while(!terminer)
    {
        SDL_RenderClear(ecran);
        SDL_RenderCopy(ecran, fond, NULL, NULL);
        SDL_RenderCopy(ecran, world.ship.obj, &SrcR, &world.ship.pos);
        //SDL_PollEvent ...
        SDL_RenderPresent(ecran);
        while( SDL_PollEvent( &evenements ) )
        switch(evenements.type)
            {
                case SDL_QUIT:
                    terminer = true; 
                    break;
                case SDL_KEYDOWN:
                    switch(evenements.key.keysym.sym){
                        case SDLK_ESCAPE:
                            terminer = true;  break;
                        case SDLK_LEFT:
                            world.ship.pos.x -= 15;
                            exceed_limit_left(&world.ship);
                            break;
                        case SDLK_RIGHT:
                            world.ship.pos.x += 15;
                            exceed_limit_right(&world.ship);
                            break;
                        case SDLK_UP:
                            world.ship.pos.y -= 15;
                            exceed_limit_up(&world.ship);
                            break;
                        case SDLK_DOWN:
                            world.ship.pos.y += 15;
                            exceed_limit_down(&world.ship);
                            break;
                    }
            }
    }

    SDL_DestroyTexture(fond);
    SDL_DestroyRenderer(ecran);
    // QUITTER SDL
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    return 0;
}