//
//  jeudelavie.h
//  Jeu de la vie
//
//  Created by Alexis Durieux on 14/02/2015.
//  Copyright (c) 2015 Alexis Durieux. All rights reserved.
//

#ifndef __Jeu_de_la_vie__jeudelavie__
#define __Jeu_de_la_vie__jeudelavie__

#include <stdio.h>

#endif /* defined(__Jeu_de_la_vie__jeudelavie__) */

#define TILEH 15
#define TILEW 15
#define TAILLE_MENU 500
#define MARGE 30

typedef enum etat etat;

enum etat
{
    MORTE, VIVANTE
};

void initialisation();
void fin();
etat** initialisationPlateau(int x, int y);
void afficherPlateau(etat **plat, int x, int y);
void ajouterElements(etat **plat, int nbElements, int x, int y);
void interationsVoisines(int x, int y, int i, int j, int **platVoisines);
void jouerTour(etat **plat, int x, int y);
void saisieElement(etat ** plat, int x, int y);
int menuSDL(SDL_Renderer *renderer);
void updatePlateauSDL(etat **plat, int x, int y, SDL_Renderer * renderer);
void drawCircle(SDL_Renderer *renderer, SDL_Point c, int r);
void ajouterElementsALaSouris(etat **plat,int  x,int y, SDL_Renderer* renderer);






