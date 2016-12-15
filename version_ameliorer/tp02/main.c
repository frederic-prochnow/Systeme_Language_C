#include <stdio.h>

#include "entiers.h"

int main(void)
{
   int tab1[] = {1, 2, 3, 4, 5, 6};
   /* Calcul de la taille du tableau.

      ATTENTION: ce calcul ne marche QUE si la déclaration du tableau
      est disponible dans le contexte du calcul.
   */
   int taille_tab1 = sizeof(tab1)/sizeof(tab1[0]);

   afficher(tab1, taille_tab1);
   printf("Somme: %d\n", somme(tab1, taille_tab1));

   /* Il faut un tableau de destination qui
      est suffisamment grand pour contenir la source
   */
   int dest[20];
   /* On utilise taille_tab1 et pas 20 ici, c'est la taille de la
    * source qui compte */
   copie_dans(dest, tab1, taille_tab1);
   int taille_dest = taille_tab1;
   
   afficher(dest, taille_dest);

   ajoute_apres(dest, taille_dest, tab1, taille_tab1);
   taille_dest += taille_tab1;
   afficher(dest, taille_dest);
   
   return 0;
}
