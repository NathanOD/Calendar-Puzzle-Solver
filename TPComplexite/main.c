//
//  main.c
//  TPComplexite
//
//  Created by Nathan Odic on 25/03/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "pieces.h"
#include "calendrier.h"

int nb_solutions = 0;

int calendrier[X_CALENDRIER][Y_CALENDRIER] = {
    0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 0, 0, 0,
};

int calendrier_boucle[X_CALENDRIER][Y_CALENDRIER] = {
    0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 0, 0, 0,
};

int idPiece[NB_PIECES_TOTAL];

int piece_tampon[X_PIECES][Y_PIECES];
int piece_tampon_2[X_PIECES][Y_PIECES];
int pieces_rotation[NB_PIECES_ROTATION][X_PIECES][Y_PIECES];
int pieces_finales[NB_PIECES_TOTAL][X_PIECES][Y_PIECES];
int pieces_init[NB_PIECES][X_PIECES][Y_PIECES] = {
    {
        0, 1, 0, 0,
        0, 1, 0, 0,
        0, 1, 0, 0,
        1, 1, 0, 0
    },
    {
        0, 1, 0, 0,
        0, 1, 0, 0,
        1, 1, 1, 0,
        0, 0, 0, 0
    },
    {
        1, 1, 1, 0,
        1, 0, 0, 0,
        1, 0, 0, 0,
        0, 0, 0, 0
    },
    {
        1, 1, 0, 0,
        0, 1, 0, 0,
        0, 1, 1, 0,
        0, 0, 0, 0
    },
    {
        0, 1, 0, 0,
        0, 1, 0, 0,
        1, 1, 0, 0,
        1, 0, 0, 0
    },
    {
        1, 0, 1, 0,
        1, 1, 1, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    },
    {
        1, 0, 0, 0,
        1, 1, 0, 0,
        1, 1, 0, 0,
        0, 0, 0, 0
    },
    {
        0, 1, 0, 0,
        0, 1, 0, 0,
        1, 1, 0, 0,
        0, 0, 0, 0
    },
    {
        1, 0, 0, 0,
        1, 1, 0, 0,
        0, 1, 0, 0,
        0, 0, 0, 0
    },
    {
        1, 1, 1, 1,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    },
};



int pieces_utilisees[NB_PIECES] = {0};
int nombre_solutions = 0;
int val = 0;
int cpt_piece = 0;

/*
void trouverSolutions(int nombre_pieces_placees, int pieces_utilisees[NB_PIECES]) {
    
    for (int k=0; k<NB_PIECES; k++) {
        printf("%d ", pieces_utilisees[k]);
    }
    printf("\n");
    
    if (nombre_pieces_placees == NB_PIECES) {
        printf("Solution trouvee\n");
        
        afficherCal(calendrier_boucle);
        nombre_solutions++;
    }
    for (int i = 0; i < NB_PIECES_TOTAL; i++) {
        if (!pieces_utilisees[idPiece[i]]) {
            for (int ligne = 0; ligne < X_CALENDRIER; ligne++) {
                for (int colonne = 0; colonne < Y_CALENDRIER; colonne++) {
                    if (validerPiece(calendrier_boucle, pieces_finales[i], ligne, colonne)) {
                        ajouterPiece(calendrier_boucle, pieces_finales[i], ligne, colonne);
                        pieces_utilisees[idPiece[i]] = 1;
                        
                        trouverSolutions(nombre_pieces_placees + 1, pieces_utilisees);
                        
                        retirerPiece(calendrier_boucle, pieces_finales[i], ligne, colonne);
                        pieces_utilisees[idPiece[i]] = 0;
                    }
                }
            }
        }
    }
}
*/

int pieces_placees[NB_PIECES] = {0};

int trouverSolutions(int nombre_pieces_placees, int pieces_utilisees[NB_PIECES], int pieces_placees[NB_PIECES]) {
    if (nombre_pieces_placees == NB_PIECES) {
        printf("Solution trouvee\n");
        for (int i = 0; i < NB_PIECES; i++) {
            pieces_placees[i] = idPiece[i];
        }
        afficherCal(calendrier_boucle);
        return 1;
    }
    for (int i = 0; i < NB_PIECES_TOTAL; i++) {
        if (!pieces_utilisees[idPiece[i]]) {
            for (int ligne = 0; ligne < X_CALENDRIER; ligne++) {
                for (int colonne = 0; colonne < Y_CALENDRIER; colonne++) {
                    if (validerPiece(calendrier_boucle, pieces_finales[i], ligne, colonne)) {
                        ajouterPiece(calendrier_boucle, pieces_finales[i], ligne, colonne);
                        pieces_utilisees[idPiece[i]] = 1;
                        //afficherCal(calendrier_boucle);
                        //printf("\n");
                        
                        if (trouverSolutions(nombre_pieces_placees + 1, pieces_utilisees, pieces_placees)) {
                            // Si cela conduit à une solution, nous sommes bons
                            
                            return 1;
                        }
                        else {
                            retirerPiece(calendrier_boucle, pieces_finales[i], ligne, colonne);
                            pieces_utilisees[idPiece[i]] = 0;
                        }
                    }
                }
            }
        }
    }
    return 0;
}



int main() {
    float temps_s = 0;
    float temps_ms = 0;
    
    indiquerJour(7, 1, 1, calendrier); //Jour[1-7], NumJour[1-31], Mois[1-12]
    indiquerJour(7, 1, 1, calendrier_boucle); //Jour[1-7], NumJour[1-31], Mois[1-12]
    //afficherCal(calendrier);
    completerPieces(pieces_init, pieces_rotation, pieces_finales, idPiece, piece_tampon, piece_tampon_2);
    trouverSolutions(0, pieces_utilisees, pieces_placees);
    
    /*
    for (int i = 0; i < NB_PIECES; i++) {
        printf("%d ", pieces_placees[i]);
    }
    */
    
    temps_ms = clock();
    temps_s = temps_ms / CLOCKS_PER_SEC;
    printf("Temps d'execution : %f secondes\n", temps_s );
    return 0;
}
