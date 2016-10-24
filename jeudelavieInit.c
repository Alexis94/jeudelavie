//
//  jeudelavieInit.c
//  Jeu de la vie
//
//  Created by Alexis Durieux on 18/02/2015.
//  Copyright (c) 2015 Alexis Durieux. All rights reserved.
//

#include "jeudelavieInit.h"
#include "jeudelavie.h"
#include <stdio.h>
#include <time.h>

etat** initialisationPlateau(int x, y){ //Initialise un tableau de x*y cellules mortes
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
