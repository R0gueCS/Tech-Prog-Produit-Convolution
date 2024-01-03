#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Constante
#define LIMITE 10000

// Prototypes de fonctions
void libererMatrice(int **, int);
int **allouerMatrice(int);
int **remplirMatriceRandom(int);
int **ajouterBordure(int **, int);
void afficherMatrice(int **, int);
int trace_matrice(int **, int);
int **conv_matrices(int **, int, int **, int);
int **enleverBordure(int **, int);

#endif // FUNCTIONS_H