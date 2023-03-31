//
//  pieces.h
//  TPComplexite
//
//  Created by Nathan Odic on 25/03/2023.
//

#ifndef pieces_h
#define pieces_h

#define NB_PIECES 10
#define NB_PIECES_ROTATION 40
#define NB_PIECES_TOTAL 34
#define NB_ROTATION 4
#define X_PIECES 4
#define Y_PIECES 4



#include <stdio.h>
#include "calendrier.h"

// Fonction affichant la pièce
void afficherPiece (int piece[X_PIECES][Y_PIECES]);

// Fonction renvoyant la pièce avec une roation de 90deg dans le sens anti-horaire
void rotationPiece (int piece[X_PIECES][Y_PIECES], int tampon[X_PIECES][Y_PIECES]);

// Fonction réalisant une copie d'une pièce
void copiePiece (int piece[X_PIECES][Y_PIECES], int copie[X_PIECES][Y_PIECES]);

// Fonction déplacant une pièce en haut à gauche du tableau 4x4 ou est définie la pièce
void deplacer_piece(int piece[X_PIECES][Y_PIECES]);

// Fonction créant une liste des 10 pièces avec toutes leurs rotations
void completerPieces (int init[NB_PIECES][X_PIECES][Y_PIECES],
                      int rotation[NB_PIECES_ROTATION][X_PIECES][Y_PIECES],
                      int finales[NB_PIECES_ROTATION][X_PIECES][Y_PIECES],
                      int id[NB_PIECES_TOTAL],
                      int tampon[X_PIECES][Y_PIECES],
                      int tampon_2[X_PIECES][Y_PIECES]);

// Fonction vérifiant si une pièce peut être placée à une case
int validerPiece(int cal[X_CALENDRIER][Y_CALENDRIER], int piece[X_PIECES][Y_PIECES], int x_cal, int y_cal);

// Fonction ajoutant une pièce à une case
void ajouterPiece(int cal[X_CALENDRIER][Y_CALENDRIER], int piece[X_PIECES][Y_PIECES], int x_cal, int y_cal);

// Fonction retirant une pièce à une case
void retirerPiece(int cal[X_CALENDRIER][Y_CALENDRIER], int piece[X_PIECES][Y_PIECES], int x_cal, int y_cal);

// Fonction renvoyant la hauteur d'une pièce
int tailleXPiece(int piece[X_PIECES][Y_PIECES]);

// Fonction renvoyant la largeur d'une pièce
int tailleYPiece(int piece[X_PIECES][Y_PIECES]);

#endif /* pieces_h */
