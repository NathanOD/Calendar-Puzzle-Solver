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

void afficherPiece (int piece[X_PIECES][Y_PIECES]);

void rotationPiece (int piece[X_PIECES][Y_PIECES], int tampon[X_PIECES][Y_PIECES]);

void copiePiece (int piece[X_PIECES][Y_PIECES], int copie[X_PIECES][Y_PIECES]);

void deplacer_piece(int piece[X_PIECES][Y_PIECES]);

void completerPieces (int init[NB_PIECES][X_PIECES][Y_PIECES],
                      int rotation[NB_PIECES_ROTATION][X_PIECES][Y_PIECES],
                      int finales[NB_PIECES_ROTATION][X_PIECES][Y_PIECES],
                      int id[NB_PIECES_TOTAL],
                      int tampon[X_PIECES][Y_PIECES],
                      int tampon_2[X_PIECES][Y_PIECES]);

int validerPiece(int cal[X_CALENDRIER][Y_CALENDRIER], int piece[X_PIECES][Y_PIECES], int x_cal, int y_cal);

void ajouterPiece(int cal[X_CALENDRIER][Y_CALENDRIER], int piece[X_PIECES][Y_PIECES], int x_cal, int y_cal);

void retirerPiece(int cal[X_CALENDRIER][Y_CALENDRIER], int piece[X_PIECES][Y_PIECES], int x_cal, int y_cal);

#endif /* pieces_h */
