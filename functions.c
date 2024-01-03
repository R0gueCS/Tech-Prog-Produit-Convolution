#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include "functions.h"

// Libérer la mémoire allouée pour la matrice
void libererMatrice(int **matrice, int n)
{
  if (matrice != NULL)
  {
    for (int i = 0; i < n; i++)
    {
      free(matrice[i]);
    }
    free(matrice);
  }
}

// Allouer la taille de la matrice
int **allouerMatrice(int n)
{
  if (n <= 0)
  {
    fprintf(stderr, "Taille de matrice invalide.\n");
    return NULL;
  }

  int **matrice = (int **)calloc(n, sizeof(int *));
  if (matrice == NULL)
  {
    fprintf(stderr, "Erreur d'allocation de mémoire.\n");
    return NULL;
  }

  for (int i = 0; i < n; i++)
  {
    matrice[i] = (int *)calloc(n, sizeof(int));
    if (matrice[i] == NULL)
    {
      fprintf(stderr, "Erreur d'allocation de mémoire.\n");
      libererMatrice(matrice, i); // Libération partielle en cas d'erreur
      return NULL;
    }
  }

  return matrice;
}

// Remplir la matrice de convolution aléatoirement
int **remplirMatriceRandom(int taille)
{
  if (taille <= 0)
  {
    fprintf(stderr, "Taille de matrice invalide.\n");
    return NULL;
  }

  int **matriceConvolution = (int **)malloc(sizeof(int *) * taille);
  if (matriceConvolution == NULL)
  {
    perror("Erreur d'allocation de mémoire pour la matrice de convolution");
    return NULL;
  }

  srand(time(NULL));

  for (int i = 0; i < taille; i++)
  {
    matriceConvolution[i] = (int *)malloc(sizeof(int) * taille);
    if (matriceConvolution[i] == NULL)
    {
      perror("Erreur d'allocation de mémoire pour la matrice de convolution");
      libererMatrice(matriceConvolution, i);
      return NULL;
    }

    for (int j = 0; j < taille; j++)
    {
      matriceConvolution[i][j] = rand() % 10;
    }
  }

  return matriceConvolution;
}

// Ajouter une bordure de 0 à la matrice
int **ajouterBordure(int **matrice, int n)
{
  int **matriceAvecBordure = allouerMatrice(n + 2);
  if (matriceAvecBordure == NULL)
  {
    return NULL;
  }

  for (int i = 0; i < n + 2; i++)
  {
    for (int j = 0; j < n + 2; j++)
    {
      if (i == 0 || i == n + 1 || j == 0 || j == n + 1)
      {
        matriceAvecBordure[i][j] = 0;
      }
      else
      {
        matriceAvecBordure[i][j] = matrice[i - 1][j - 1];
      }
    }
  }

  return matriceAvecBordure;
}


// Affichage de la matrice
void afficherMatrice(int **matrice, int n)
{
  if (matrice == NULL)
  {
    fprintf(stderr, "Matrice invalide.\n");
    return;
  }

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      printf("%5d ", matrice[i][j]); // Format amélioré pour l'affichage
    }
    printf("\n");
  }
}

// Calcul de la trace de la matrice
int traceMatrice(const int **matrice, int n)
{
  int trace = 0;
  for (int i = 0; i < n; i++)
  {
    trace += matrice[i][i];
  }

  return trace;
}

// Produit convolutionnel
int **conv_matrices(int **A, int n, int **B, int p)
{
  // Assuming allouerMatrice(n) allocates memory for an (n+2) x (n+2) matrix and returns it
  int **matrice = allouerMatrice(n + 2);

  for (int j = 0; j < n; j++)
  {
    for (int i = 0; i < n; i++)
    {
      int somme = 0;
      for (int y = 0; y < p; y++)
      {
        for (int x = 0; x < p; x++)
        {
          somme += A[i + y][j + x] * B[y][x];
        }
      }
      matrice[i + 1][j + 1] = somme;
    }
  }

  return matrice;
}

// Enlever les bordures de la matrice
int **enleverBordure(int **matriceAvecBordure, int n)
{
  if (matriceAvecBordure == NULL || n <= 2)
  {
    return NULL;
  }

  int **matriceSansBordure = allouerMatrice(n - 2);
  if (matriceSansBordure == NULL)
  {
    return NULL;
  }

  for (int i = 0; i < n - 2; i++)
  {
    for (int j = 0; j < n - 2; j++)
    {
      matriceSansBordure[i][j] = matriceAvecBordure[i + 1][j + 1];
    }
  }

  return matriceSansBordure;
}
