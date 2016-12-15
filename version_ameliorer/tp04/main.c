#include <stdio.h>
#include <stdlib.h>

#include "fonctions.h"

void mauvaise_utilisation(void)
{
   fprintf(stderr, "Mauvaise utilisation\n");
}

int main(int argc, char **argv)
{

   /* On va parcourir les options et simplement mettre à 1 nos flags
    * si on trouve un s ou un m */
   int s = 0, m = 0;
   int i;
   /* On commence à 1 car argv[0] correspond au nom de la commande 
      Le test de boucle vérifie si l'argument est une option (commence par '-').
      Ce test vient APRES le i < argc, car il ne peut être valide que dans ce cas
    */
   for (i = 1 ; i < argc && argv[i][0] == '-' ; ++i)
   {
      /* On parcours l'option */
      for (int j = 1 ; argv[i][j] != '\0'; ++j)
      {
         switch (argv[i][j])
         {
            case 's': s = 1; break;
            case 'm': m = 1; break;
            default: /* autre chose qu'un s ou un m */
               mauvaise_utilisation();
               return 1;
         }
      }
   }
   /* A la fin de la boucle, i est l'indice du premier argument qui
    * n'est pas une option */

   if (s && i != argc) 
   {
      /* On demande une saisie, mais on donne un mot sur la ligne de commande */
      mauvaise_utilisation();
      return 2;
   }
   if (!s && i == argc)
   {
      /* on ne demande pas de saisie, mais on ne donne pas de mot sur la ligne de commande */
      mauvaise_utilisation();
      return 3;
   }
   char *source;
   /* Si on a demandé une saisie, on la fait, sinon, on prend le mot de la ligne de commande */
   if (s)
   {
      source = saisie();
      if (source == NULL)
         return 4;
   }
   else
      source = argv[i];
   /* Si on a demandé un miroir, on le fait */
   if (m)
   {
      char *mir = miroir(source);
      if (mir == NULL)
      {
         if (s)
            free(source);
         return 5;
      }
      printf("%s\n", mir);
      free(mir);
   }
   else /* sinon, on affiche la source directement */
      printf("%s\n", source);
   /* Enfin si on a fait une saisie, on libère la chaîne. Attention,
    * uniquement dans ce cas, sinon cela équivaut à faire un
    * free(argv[i]) -> Erreur de segmentation */
   if (s)
      free(source);
   return 0;
}
