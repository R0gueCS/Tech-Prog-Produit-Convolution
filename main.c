#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "functions.h"

#define TAILLE_MATRICE 3
#define TAILLE_MATRICE_CONVOLUTION 2


int main()
{
    int n = TAILLE_MATRICE;

    int **A = remplirMatriceRandom(n);

    printf("La matrice A avant convolution :\n");
    afficherMatrice(A, n);

    int **A_avec_bordures = ajouterBordure(A, n);

    int **B = remplirMatriceRandom(TAILLE_MATRICE_CONVOLUTION);

    printf("La matrice B :\n");
    afficherMatrice(B, TAILLE_MATRICE_CONVOLUTION);

    int **conv = conv_matrices(A_avec_bordures, n, B, TAILLE_MATRICE_CONVOLUTION);

    printf("Résultat de la convolution avec bordures :\n");
    afficherMatrice(conv, n + 2);

    int **conv_sans_bordures = enleverBordure(conv, n + 2);

    printf("Résultat de la convolution sans bordures :\n");
    afficherMatrice(conv_sans_bordures, n);

    libererMatrice(A, n);
    libererMatrice(A_avec_bordures, n + 2);
    libererMatrice(B, TAILLE_MATRICE_CONVOLUTION);
    libererMatrice(conv, n + 2);
    libererMatrice(conv_sans_bordures, n);

    return 0;
}
