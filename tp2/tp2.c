#include <stdio.h>

void afficher(int liste[],int taille)
{
  int i;
  for(i=0;i<taille;i++)
  {
    printf("valeur %d : %d\n",i,liste[i]);
  }
}

int somme (int liste[],int taille)
{
  int i;
  int res=0;
  for(i=0; i<taille;i++) 
  {
    res+=liste[i];
  }
  return res;  
}

void copie_dans(int dest[],int src[],int taille)
{
  int i;
  //int mem;
  for(i=0; i<taille;i++)
  {
    /*mem=src[i];
    src[i]=dest[i];
    dest[i]=mem;*/
    dest[i]=src[i];
  }
}

void ajoute_apres(int dest[], int taille_dest, int src[], int taille_src)
{
  int i;
  int j=0;
  for(i=taille_dest; i<(taille_dest + taille_src); i++) 
  {
    dest[i] = src[j];
    j++;
  } 
}

int main(void)
{
  int liste1 [] = {1,2,4,8,16,32,64};
  printf("liste 1: \n");
  afficher(liste1,7);
  printf("somme liste 1 : %i\n",somme(liste1,7));
  int liste2 [] = {65,66,67,68,69,70,71};
  printf("liste 2: \n");
  afficher(liste2,7);
  printf("somme liste 2 : %i\n",somme(liste2,7));
  printf("deplacement de liste 2 dans liste 1 ... \n");
  ajoute_apres(liste1,7,liste2,7);
  printf("liste 1 apres deplacement: \n");
  afficher(liste1,14);
  printf("somme liste 1 apres deplacement : %i\n",somme(liste1,14));
  int liste3 [14];
  printf("copie de liste1 dans liste 3 ... \n ");
  copie_dans(liste3,liste1,14);
  printf("liste 3: \n");
  afficher(liste3,14);
  printf("somme liste 3 : %i\n",somme(liste3,14));
  return 0; 
}
