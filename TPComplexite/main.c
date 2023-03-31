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

int pieces_tot = 0; // Le nombre de pièces ajoutées au calendrier lors de la résolution
int compteur = 0; // Compteur pour savoir quelle pièce a été placée dans le calendrier
int resultat = 0; // Résultat de la fonction récursive (nombre de solutions)

int idPiece[NB_PIECES_TOTAL]; // Tableau contenant le numéro de la pièce (1-10) associée à une pièce avec une roation
int pieces_utilisees[NB_PIECES] = {0}; // Tableau des pièces utilisées
int pieces_placees[3][NB_PIECES] = {0}; //Tableau des pièces placées dans le calendrier

// Définition du calendrier
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
// Initialisation des différentes pièces
int piece_tampon[X_PIECES][Y_PIECES];
int piece_tampon_2[X_PIECES][Y_PIECES];
int pieces_rotation[NB_PIECES_ROTATION][X_PIECES][Y_PIECES];
int pieces_finales[NB_PIECES_TOTAL][X_PIECES][Y_PIECES];
// Définitions des pièces
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

// Fonction solveur récursive
int trouverSolutions(int x, int y) {
    // Si toutes les pièces ont été placées, on renvoie 1
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
        return 1;
    }
    // Si les coordonnées ne sont pas valides, on revoie 0
    if (x>=X_CALENDRIER || y>=Y_CALENDRIER) {
        return 0;
    }
    // On initialise la variable resolu qui prend la valeur 1 si la case est vide
    int resolu = 0;
    if (!calendrier[x][y]) {
        resolu = 1;
    }
    // On boucle sur toutes les pièces possibles
    for (int id_piece=0; id_piece<NB_PIECES_TOTAL; id_piece++) {
        // On vérifie que la pièce n'a pas déjà été placée
        if (!pieces_utilisees[idPiece[id_piece]]) {
            // On passe à la pièce suivante si la pièce sort du calendrier
            if ((x + tailleXPiece(pieces_finales[id_piece]) > X_CALENDRIER) || (y + tailleYPiece(pieces_finales[id_piece]) > Y_CALENDRIER)) {
                continue;
            }
            // On passe à la pièce suivante si la pièce ne peut pas être placée
            if (!validerPiece(calendrier, pieces_finales[id_piece], x, y)) {
                continue;
            }
            // On ajoute la pièce
            ajouterPiece(calendrier, pieces_finales[id_piece], x, y);
            // On ajoute la pièce à la liste des pièces utilisées
            pieces_utilisees[idPiece[id_piece]] = 1;
            // On ajoute l'id et les coordonnées de la pièce à la liste des pièces placée
            pieces_placees[0][compteur] = id_piece;
            pieces_placees[1][compteur] = x;
            pieces_placees[2][compteur] = y;
            // On incrémente le nombre de pièces placées
            compteur++;
            pieces_tot++;
            if (resolu && !calendrier[x][y]) {
                // On retire la pièce
                retirerPiece(calendrier, pieces_finales[id_piece], x, y);
                // On retire la pièce à la liste des pièces utilisées
                pieces_utilisees[idPiece[id_piece]] = 0;
                // On retire l'id et les coordonnées de la pièce à la liste des pièces placée
                pieces_placees[0][compteur-1] = 0;
                pieces_placees[1][compteur-1] = 0;
                pieces_placees[2][compteur-1] = 0;
                // On décrémente le nombre de pièces placées
                compteur--;
                pieces_tot--;
                continue;
            }
            // On appelle la focntion récursive avec les nouvelles coordonnées
            int n_x = (x * Y_CALENDRIER + y + 1) / Y_CALENDRIER;
            int n_y = (x * Y_CALENDRIER + y + 1) % Y_CALENDRIER;
            resultat += trouverSolutions(n_x, n_y);
            // On retire la pièce
            retirerPiece(calendrier, pieces_finales[id_piece], x, y);
            pieces_utilisees[idPiece[id_piece]] = 0;
            pieces_tot--;
            pieces_placees[0][compteur-1] = 0;
            pieces_placees[1][compteur-1] = 0;
            pieces_placees[2][compteur-1] = 0;
            compteur--;
        }
    }
    if (!resolu) {
        // On appelle la focntion récursive avec les nouvelles coordonnées
        int n_x = (x * Y_CALENDRIER + y + 1) / Y_CALENDRIER;
        int n_y = (x * Y_CALENDRIER + y + 1) % Y_CALENDRIER;
        resultat += trouverSolutions(n_x, n_y);
    }
    // Fin de la fonction
    return 0;
}


int main() {
    float temps_s = 0;
    float temps_ms = 0;
    
    indiquerJour(6, 1, 1, calendrier); //Jour[1-7] (Lundi-Dimanche), NumJour[1-31], Mois[1-12]
    //afficherCal(calendrier);
    //printf("\n");
    completerPieces(pieces_init, pieces_rotation, pieces_finales, idPiece, piece_tampon, piece_tampon_2);
    
    trouverSolutions(0, 0);
    printf("Nombre de solutions : %d\n", resultat);
    
    temps_ms = clock();
    temps_s = temps_ms / CLOCKS_PER_SEC;
    printf("Temps d'execution : %f secondes\n", temps_s );
    return 0;
}
