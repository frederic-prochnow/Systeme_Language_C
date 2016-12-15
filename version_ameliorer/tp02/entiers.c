#include <stdio.h>

void afficher(int liste[], int taille)
{
   int i;
   for (i = 0 ; i < taille ; ++i)
      printf("%d ", liste[i]);
   printf("\n");
}

int  somme (int liste[], int taille)
{
   int i, sum = 0;
   for (i = 0 ; i < taille; ++i)
      sum += liste[i];
   return sum;
}

void copie_dans(int dest[], int src[], int taille)
{
   int i;
   for (i = 0 ; i < taille ; ++i)
      dest[i] = src[i];
}

void ajoute_apres(int dest[], int taille_dest, int src[], int taille_src)
{
   int i;
   for (i = 0 ; i < taille_src ; ++i)
      dest[i+taille_dest] = src[i];
}
