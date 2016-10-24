//
//  jeudelavie.c
//  Jeu de la vie
//
//  Created by Alexis Durieux on 14/02/2015.
//  Copyright (c) 2015 Alexis Durieux. All rights reserved.
//

#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "jeudelavie.h"

void initialisation(){ //Initialise SDL et TTF
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stdout,"Initialisation : %s",SDL_GetError());
    }
    if (TTF_Init() != 0) {
        fprintf(stdout,"Erreur TTF_Init : %s", SDL_GetError());
    }
}

void fin(){ //Quitte SDL et TTF
    TTF_Quit();
    SDL_Quit();
}


etat** initialisationPlateau(int x, int y){ //Initialise un tableau de x*y cellules mortes
    int i, j = 0;
    
    etat **plat = malloc(sizeof(etat*)*x);
    for (i = 0; i < x; i++) {
        plat[i] = malloc(sizeof(etat)*y);
    }
    
    if (plat != NULL){ //On initialise toutes les cellules à mortes au début
        for (i = 0; i < x; i++) {
            for (j = 0; j <= y; j++) {
                plat[i][j] = MORTE;
            }
        }
        return plat;
    }
    
    return NULL;
}


void afficherPlateau(etat **plat, int x, int y){ //Affichage du plateau en console
    
    int i, j = 0;
    
    for (i = 0; i < x; i++) {
        for (j = 0 ; j < y ; j++) {
            printf("%d ", plat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void ajouterElements(etat **plat, int nbElements, int x, int y){ //Ajoute nbElements cellules vivantes sur le plateau
    int i, xRand, yRand = 0;                             //aléatoirement.
    while (i < nbElements) {
        xRand = rand() % x;
        yRand = rand() % y;
        if (plat[xRand][yRand] == MORTE) {
            plat[xRand][yRand] = VIVANTE;
            i++;
        }
    }
}

void iterationsVoisines(int x, int y, int i, int j, int **platVoisines){ //Si une cellule de coordonnées i, j est vivante,
    int k, l, borneSupi, borneSupj = 0;                      //ajoute 1 à toutes les cellules voisines dans la
    borneSupi = i + 1;                                       //à la matrice du nbre de cellules vivantes voisines
    borneSupj = j + 1;
    if (i + 1 == x) borneSupi--;
    if (j + 1 == y) borneSupj--;
    
    for (k = i - 1; k <= borneSupi; k++) {
        for (l = j - 1; l <= borneSupj; l++) {
            if (k == -1) k++;
            if (l == -1) l++;
            if (!(k == i && l == j)) {
                platVoisines[k][l]++;
            }
        }
    }
}


void jouerTour(etat **plat, int x, int y){ //Effectuer un tour
    
    int i, j = 0;
    
    int **platVoisines = malloc(sizeof(int*)*x); //On crée la variable platVoisine
    for (i = 0; i < x; i++) {
        platVoisines[i] = calloc(sizeof(int)*y, sizeof(int));
    }
    
    for (i = 0; i < x; i++) {
        for (j = 0; j < y; j++) {
            if (plat[i][j] == VIVANTE) {
                iterationsVoisines(x, y, i, j, platVoisines);
            }
        }
    }
    for (i = 0; i < x; i++) {
        for (j = 0 ; j < y ; j++) {
            if (platVoisines[i][j] == 3) {
                plat[i][j] = VIVANTE;
            }else if (platVoisines[i][j] < 2 || platVoisines[i][j] > 3){
                plat[i][j] = MORTE;
            }
        }
    }
    
    for(i = 0; i < x; i++) { //On libère la mémoire
        free(platVoisines[i]);
        platVoisines[i] = NULL;
    }
}

void saisieElement(etat ** plat, int x, int y){
    int i, j = 0;
        printf("X = "); scanf("%d", &i);
        printf("Y = "); scanf("%d", &j);
    plat[i][j] = VIVANTE;
}


void updatePlateauSDL(etat **plat, int x, int y, SDL_Renderer * renderer){
    int i, j = 0;
    SDL_Rect rect = {0};
    rect.h = TILEH;
    rect.w = TILEW;
    
    for (i = 0; i < x; i++) {
        for (j = 0; j < y; j++) {
            rect.x = TILEW*i;
            rect.y = TILEH*j;
            if (plat[i][j] == VIVANTE) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &rect);
            }else if (plat[i][j] == MORTE){
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &rect);
            }
            SDL_SetRenderDrawColor(renderer, 102, 102, 102, 100);
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}



int menuSDL(SDL_Renderer * renderer){
    
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    //Affichage des textes
    TTF_Font * font = TTF_OpenFont("/Library/Fonts/Pilgiche.ttf", TAILLE_MENU/10);
    SDL_Color textColor =  {255,255,255};
    char* aleatoire = "Hasard !";
    char* choisir = "Choisir !";
    SDL_Surface * textSurf = TTF_RenderText_Blended(font, aleatoire, textColor);
    if (textSurf) {
        SDL_Texture * TextTexture = SDL_CreateTextureFromSurface(renderer, textSurf);
        SDL_Rect rect;
        rect.x = TAILLE_MENU/2 - TAILLE_MENU/11;
        rect.y = TAILLE_MENU/5;
        rect.w = TAILLE_MENU/5;
        rect.h = TAILLE_MENU/10;
        SDL_RenderCopy(renderer, TextTexture, NULL, &rect);
        rect.y = 5*TAILLE_MENU/7;
        textSurf = TTF_RenderText_Blended(font, choisir, textColor);
        TextTexture = SDL_CreateTextureFromSurface(renderer, textSurf);
        SDL_RenderCopy(renderer, TextTexture, NULL, &rect);
        TTF_CloseFont(font);
        SDL_FreeSurface(textSurf);
    }
    
    //Affichage des cercles
    int r = TAILLE_MENU/8;
    SDL_Point centre;
    r = TAILLE_MENU/8;
    centre.x = TAILLE_MENU/2; centre.y = TAILLE_MENU/4;
    drawCircle(renderer, centre, r); //Affiche le cercle pour "JOUER";
    centre.y = 3*TAILLE_MENU/4;
    drawCircle(renderer, centre, r);
    SDL_RenderPresent(renderer);
    
    //Évènements liés au menu (Jouer ou quitter)
    SDL_Event e;
    int choix = 3;
    int x, y = 0;
    while (choix != 0 && choix != 1 && choix != 2) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                SDL_GetMouseState(&x, &y);
                if (((x - TAILLE_MENU/2)*(x - TAILLE_MENU/2) + (y - TAILLE_MENU/4)*(y - TAILLE_MENU/4)) < (r + 1/2)*(r + 1/2)) {
                    choix = 1; //Aléatoire !
                }else if(((x - TAILLE_MENU/2)*(x - TAILLE_MENU/2) + (y - 3*TAILLE_MENU/4)*(y - 3*TAILLE_MENU/4)) < (r + 1/2)*(r + 1/2)){
                    choix = 2; //Choix ! 
                }
            }else if (e.type == SDL_QUIT){
                choix = 0; //Quitter
            }
        }
    }
    return choix;
}

void drawCircle(SDL_Renderer *renderer, SDL_Point c, int r){ //Algorithme de tracé de cercle d'andrès
    int x = 0, y = r, d = r - 1;
    while (y >= x) {
        SDL_RenderDrawPoint(renderer, c.x + x, c.y + y);
        SDL_RenderDrawPoint(renderer, c.x + y, c.y + x);
        SDL_RenderDrawPoint(renderer, c.x - x, c.y + y);
        SDL_RenderDrawPoint(renderer, c.x - y, c.y + x);
        SDL_RenderDrawPoint(renderer, c.x + x, c.y - y);
        SDL_RenderDrawPoint(renderer, c.x + y, c.y - x);
        SDL_RenderDrawPoint(renderer, c.x - x, c.y - y);
        SDL_RenderDrawPoint(renderer, c.x - y, c.y - x);
        if (d >= 2*x) {
            d = d - 2*x - 1;
            x = x + 1;
        }else if (d < 2*(r-y)){
            d = d + 2*y - 1;
            y = y - 1;
        }else{
            d = d + 2*(y-x-1);
            y = y - 1;
            x = x + 1;
        }
    }
}


//---------TEST TRACÉ DE CERCLE---------
/*for (i = 3*TAILLE_MENU/8; i <= 5*TAILLE_MENU/8; i++) {
 p.x = i;
 p.y = sqrt(r*r - ((p.x - (TAILLE_MENU/2))*(p.x - (TAILLE_MENU/2)))) + TAILLE_MENU/4;
 SDL_RenderDrawPoint(renderer, p.x, p.y);
 p.y = p.y - 2*(p.y - TAILLE_MENU/4);
 SDL_RenderDrawPoint(renderer, p.x, p.y);
 }*/



void ajouterElementsALaSouris(etat **plat,int  x,int y, SDL_Renderer* renderer){    
    SDL_Event e;
    int i, j, debut = 0;
    double a, b = 0;
    SDL_Keycode k;
    while (!debut) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                SDL_GetMouseState(&i, &j);
                if (i < TILEW*x && j < TILEH*y) {
                    a = i/TILEW;
                    b = j/TILEH;
                    i = floor(a);
                    j = floor(b);
                    if (plat[i][j] == MORTE) {
                        plat[i][j] = VIVANTE;
                    }else if (plat[i][j] == VIVANTE){
                        plat[i][j] = MORTE;
                    }
                    updatePlateauSDL(plat, x, y, renderer);
                    SDL_RenderPresent(renderer);
                }
            }
            if (e.type == SDL_KEYDOWN){
                if (e.key.keysym.sym == SDLK_f){
                    debut = 1;
                }
            }
        }
    }
}
