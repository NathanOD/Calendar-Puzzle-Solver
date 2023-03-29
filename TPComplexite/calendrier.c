//
//  calendrier.c
//  TPComplexite
//
//  Created by Nathan Odic on 25/03/2023.
//

#include "calendrier.h"

void afficherCal (int cal[X_CALENDRIER][Y_CALENDRIER]) {
    for (int i=0; i<X_CALENDRIER; i++) {
        for (int j=0; j<Y_CALENDRIER; j++) {
            printf("%d ", cal[i][j]);
        }
        printf("\n");
    }
}

void indiquerJour(int jour, int numJour, int mois, int cal[X_CALENDRIER][Y_CALENDRIER]) {
    int x_jour, y_jour;
    if (jour<4) {
        x_jour = 6;
        y_jour = jour + 3;
    }
    else if (jour<7) {
        x_jour = 7;
        y_jour = jour;
    }
    else {
        x_jour = 6;
        y_jour = 3;
    };
    cal[x_jour][y_jour] = 1;
    
    int x_numJour, y_numJour;
    x_numJour = (numJour-1) / 7 + 2;
    y_numJour = (numJour-1) % 7;
    cal[x_numJour][y_numJour] = 1;
    
    int x_mois, y_mois;
    if (mois<7) {
        x_mois = 0;
        y_mois = mois - 1;
    }
    else {
        x_mois = 1;
        y_mois = mois - 7;
    };
    cal[x_mois][y_mois] = 1;
}
