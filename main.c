//
//  main.c
//  Jeu de la vie
//
//  Created by Alexis Durieux on 14/02/2015.
//  Copyright (c) 2015 Alexis Durieux. All rights reserved.
//

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jeudelavie.h"

int main(int argc, const char * argv[]) {
    
    //Initialisation des variables
    int stop = 0;
    int quit = 0;
    int nbElements, x, y= 0;
    etat** plateau = NULL;
    SDL_Event e;
    
    //Fonction pour randomize
    srand(time(NULL));
    
    //Initialisation SDL et TTF
    initialisation();
    
    SDL_Window* pWindow = NULL;
    

    pWindow = SDL_CreateWindow("Jeu de la vie",SDL_WINDOWPOS_CENTERED, //Création de la fenêtre
                               SDL_WINDOWPOS_CENTERED,
                               (TAILLE_MENU),
                               (TAILLE_MENU),
                               SDL_WINDOW_SHOWN);
    
    if(!pWindow){
        fprintf(stderr,"Window : %s",SDL_GetError());
    }else{
        SDL_Renderer * renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED); //On crée le renderer
        switch (menuSDL(renderer)) {
            case 1:
                //Quelle taille fait le plateau?
                printf("Quelle taille va faire votre plateau?\n");
                printf("X = "); scanf("%d", &x);
                printf("Y = "); scanf("%d", &y);
                plateau = initialisationPlateau(x, y);
                
                //On ajoute les éléments
                printf("Combien d'éléments voulez vous ajouter? \n"); scanf("%d", &nbElements);
                ajouterElements(plateau, nbElements, x, y);
                SDL_SetWindowSize(pWindow, x*TILEW, y*TILEH);
                SDL_SetWindowTitle(pWindow, "Jeu de la vie");
                
                if (renderer){
                    while (!quit) {
                        while (SDL_PollEvent(&e) != 0) {
                            if (e.type == SDL_QUIT) {
                                quit = 1;
                            }
                        }
                        SDL_RenderPresent(renderer);
                        jouerTour(plateau, x, y);
                        updatePlateauSDL(plateau, x, y, renderer);
                        SDL_Delay(100);
                    }
                }
                break;
                
            case 2:
                //Quelle taille fait le plateau?
                printf("Quelle taille va faire votre plateau?\n");
                printf("X = "); scanf("%d", &x);
                printf("Y = "); scanf("%d", &y);
                plateau = initialisationPlateau(x, y);
                
                SDL_SetWindowSize(pWindow, x*TILEW, y*TILEH);
                SDL_SetWindowTitle(pWindow, "Jeu de la vie");

                updatePlateauSDL(plateau, x, y, renderer);
                SDL_RenderPresent(renderer);
                ajouterElementsALaSouris(plateau, x, y, renderer);
                if (renderer){
                    while (!quit) {
                        while (SDL_PollEvent(&e) != 0) {
                            if (e.type == SDL_QUIT) {
                                quit = 1;
                            }
                            if (e.type == SDL_KEYDOWN){
                                if (e.key.keysym.sym == SDLK_p){
                                    if (stop) {
                                        stop = 0;
                                    }else if (!stop){
                                        stop = 1;
                                    }
                                }
                            }
                        }
                        if (!stop) {
                            SDL_RenderPresent(renderer);
                            jouerTour(plateau, x, y);
                            updatePlateauSDL(plateau, x, y, renderer);
                            SDL_Delay(100);
                        }
                    }
                }
                break;
                
            default:
                printf("Erreur ! \n");
                break;
        }
    }
    fin();
}
