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

int pieces_tot = 0;
int compteur = 0;
int resultat = 0;

int idPiece[NB_PIECES_TOTAL];
int pieces_utilisees[NB_PIECES] = {0};
int pieces_placees[3][NB_PIECES] = {0};

int calendrier[X_CALENDRIER][Y_CALENDRIER] = {
    0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 0, 0, 0
};

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

int trouverSolutions(int cal[X_CALENDRIER][Y_CALENDRIER], int finales[NB_PIECES][X_PIECES][Y_PIECES], int x, int y) {
    if (pieces_tot == NB_PIECES) {
        /*
        printf("Solution trouvee %d\n",nb_solutions+1);
        //afficherCal(calendrier);
        //printf("\n");
        for (int i=0; i<NB_PIECES; i++) {
            printf("%d ",idPiece[pieces_placees[0][i]]);
        }
        printf("\n");
        */
        nb_solutions++;
        return 1;
    }
    
    if (x>=X_CALENDRIER || y>=Y_CALENDRIER) {
        return 0;
    }
    int resolu = 0;
    if (!cal[x][y]) {
        resolu = 1;
    }
    else {
        resolu = 0;
    }
    for (int id_piece=0; id_piece<NB_PIECES_TOTAL; id_piece++) {
        if (!pieces_utilisees[idPiece[id_piece]]) {
            if ((x + tailleXPiece(finales[id_piece]) > X_CALENDRIER) || (y + tailleYPiece(finales[id_piece]) > Y_CALENDRIER)) {
                continue;
            }
            if (!validerPiece(cal, finales[id_piece], x, y)) {
                continue;
            }
            ajouterPiece(cal, finales[id_piece], x, y);
            pieces_utilisees[idPiece[id_piece]] = 1;
            pieces_placees[0][compteur] = id_piece;
            pieces_placees[1][compteur] = x;
            pieces_placees[2][compteur] = y;
            compteur++;
            pieces_tot++;
            if (resolu && !cal[x][y]) {
                retirerPiece(cal, finales[id_piece], x, y);
                pieces_utilisees[idPiece[id_piece]] = 0;
                pieces_tot--;
                pieces_placees[0][compteur-1] = 0;
                pieces_placees[1][compteur-1] = 0;
                pieces_placees[2][compteur-1] = 0;
                compteur--;
                continue;
            }
            int n_x = (x * Y_CALENDRIER + y + 1) / Y_CALENDRIER;
            int n_y = (x * Y_CALENDRIER + y + 1) % Y_CALENDRIER;
            resultat = trouverSolutions(cal, finales, n_x, n_y);
            retirerPiece(cal, finales[id_piece], x, y);
            pieces_utilisees[idPiece[id_piece]] = 0;
            pieces_tot--;
            pieces_placees[0][compteur-1] = 0;
            pieces_placees[1][compteur-1] = 0;
            pieces_placees[2][compteur-1] = 0;
            compteur--;
        }
    }
    if (!resolu) {
        int n_x = (x * Y_CALENDRIER + y + 1) / Y_CALENDRIER;
        int n_y = (x * Y_CALENDRIER + y + 1) % Y_CALENDRIER;
        resultat = trouverSolutions(cal, finales, n_x, n_y);
    }
    return 0;
}


int main() {
    float temps_s = 0;
    float temps_ms = 0;
    
    indiquerJour(6, 1, 1, calendrier); //Jour[1-7], NumJour[1-31], Mois[1-12]
    //afficherCal(calendrier);
    //printf("\n");
    completerPieces(pieces_init, pieces_rotation, pieces_finales, idPiece, piece_tampon, piece_tampon_2);
    
    trouverSolutions(calendrier, pieces_finales, 0, 0);
    printf("Nombre de solutions : %d\n", nb_solutions);
    
    temps_ms = clock();
    temps_s = temps_ms / CLOCKS_PER_SEC;
    printf("Temps d'execution : %f secondes\n", temps_s );
    return 0;
}
