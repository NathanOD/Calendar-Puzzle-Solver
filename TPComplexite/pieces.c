//
//  pieces.c
//  TPComplexite
//
//  Created by Nathan Odic on 25/03/2023.
//

#include "pieces.h"



void afficherPiece (int piece[X_PIECES][Y_PIECES]) {
    for (int i=0; i<X_PIECES; i++) {
        for (int j=0; j<Y_PIECES; j++) {
            printf("%d ", piece[i][j]);
        }
        printf("\n");
    }
}

// Roation de 90° (sens anti-horaire)
void rotationPiece (int piece[X_PIECES][Y_PIECES], int tampon[X_PIECES][Y_PIECES]) {
    for (int i=0; i<Y_PIECES; i++) {
        for (int j=0; j<X_PIECES; j++) {
            tampon[3-j][i] = piece[i][j];
        }
    }
}

void copiePiece (int piece[X_PIECES][Y_PIECES], int copie[X_PIECES][Y_PIECES]) {
    for (int i=0; i<Y_PIECES; i++) {
        for (int j=0; j<X_PIECES; j++) {
            copie[i][j] = piece[i][j];
        }
    }
}

void deplacer_piece(int piece[X_PIECES][Y_PIECES]) {
    int i, j;
    int minX = X_PIECES, minY = Y_PIECES;
    
    // Trouver les coordonnées minimales de la pièce
    for (i = 0; i < X_PIECES; i++) {
        for (j = 0; j < Y_PIECES; j++) {
            if (piece[i][j] != 0 && i < minX) {
                minX = i;
            }
            if (piece[i][j] != 0 && j < minY) {
                minY = j;
            }
        }
    }
    
    // Déplacer la pièce en haut à gauche
    for (i = minX; i < X_PIECES; i++) {
        for (j = minY; j < Y_PIECES; j++) {
            piece[i - minX][j - minY] = piece[i][j];
        }
    }
    
    // Remplir les éléments en dehors de la pièce avec des zéros
    for (i = 0; i < X_PIECES; i++) {
        for (j = 0; j < Y_PIECES; j++) {
            if (i < X_PIECES - minX && j < Y_PIECES - minY) {
                continue;
            }
            piece[i][j] = 0;
        }
    }
}

void completerPieces (int init[NB_PIECES][X_PIECES][Y_PIECES],
                      int rotation[NB_PIECES_ROTATION][X_PIECES][Y_PIECES],
                      int finales[NB_PIECES_TOTAL][X_PIECES][Y_PIECES],
                      int id[NB_PIECES_TOTAL],
                      int tampon[X_PIECES][Y_PIECES],
                      int tampon_2[X_PIECES][Y_PIECES]) {
    int compteur = 0;
    for (int i=0; i<NB_PIECES_ROTATION; i+=4) {
        copiePiece(init[i/4], tampon);
        for (int j=0; j<NB_ROTATION; j++) {
            copiePiece(tampon, rotation[i+j]);
            rotationPiece(tampon, tampon_2);
            copiePiece(tampon_2, tampon);
        }
    }
    for (int i=0; i<NB_PIECES_ROTATION; i++) {
        if (i != 14 && i != 15 && i != 34 && i != 35 && i != 38 && i != 39) {
            copiePiece(rotation[i], finales[compteur]);
            deplacer_piece(finales[compteur]);
            id[compteur] = i/4;
            compteur++;
        }
    }
}

int validerPiece(int cal[X_CALENDRIER][Y_CALENDRIER], int piece[X_PIECES][Y_PIECES], int x_cal, int y_cal) {
    int taille_x = 0;
    int taille_y = 0;
    for (int i = 0; i < X_PIECES; i++) {
        for (int j = 0; j < Y_PIECES; j++) {
            if (piece[i][j]) {
                //printf("%d,%d\n", i,j);
                if (i+1 > taille_x) {
                    taille_x = i+1;
                }
                if (j+1 > taille_y) {
                    taille_y = j+1;
                }
            }
        }
    }
    
    if (x_cal < 0 || y_cal < 0 || x_cal + taille_x > X_CALENDRIER || y_cal + taille_y > Y_CALENDRIER) {
        return 0;
    }
    for (int i = 0; i < X_PIECES; i++) {
        for (int j = 0; j < Y_PIECES; j++) {
            if (piece[i][j] && cal[x_cal+i][y_cal+j]) {
                return 0;
            }
        }
    }
    return 1;
}

void ajouterPiece(int cal[X_CALENDRIER][Y_CALENDRIER], int piece[X_PIECES][Y_PIECES], int x_cal, int y_cal) {
    for (int i = 0; i < X_PIECES; i++) {
        for (int j = 0; j < Y_PIECES; j++) {
            if (piece[i][j]) {
                cal[x_cal+i][y_cal+j] = 1;
            }
        }
    }
}

void retirerPiece(int cal[X_CALENDRIER][Y_CALENDRIER], int piece[X_PIECES][Y_PIECES], int x_cal, int y_cal) {
    for (int i = 0; i < X_PIECES; i++) {
        for (int j = 0; j < Y_PIECES; j++) {
            if (piece[i][j]) {
                cal[x_cal+i][y_cal+j] = 0;
            }
        }
    }
}



int tailleXPiece(int piece[X_PIECES][Y_PIECES]) {
    int nb_lignes = 0;
    for (int i = 0; i < X_PIECES; i++) {
        int ligne_non_nulle = 0;
        for (int j = 0; j < Y_PIECES; j++) {
            if (piece[i][j]) {
                ligne_non_nulle = 1;
                break;
            }
        }
        if (ligne_non_nulle) {
            nb_lignes++;
        }
    }
    return nb_lignes;
}

int tailleYPiece(int piece[X_PIECES][Y_PIECES]) {
    int nb_colonnes = 0;
    for (int j = 0; j < Y_PIECES; j++) {
        int colonne_non_nulle = 0;
        for (int i = 0; i < X_PIECES; i++) {
            if (piece[i][j]) {
                colonne_non_nulle = 1;
                break;
            }
        }
        if (colonne_non_nulle) {
            nb_colonnes++;
        }
    }
    return nb_colonnes;
}
