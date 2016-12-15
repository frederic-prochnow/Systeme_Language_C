#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char *miroir(const char *str)
{
   int taille = strlen(str);
   char *mir = malloc(taille + 1); /* le +1 est important, il sert à stocker le caractère \0 */
   if (mir == NULL)
   {
      perror("miroir(): malloc()");
      return NULL;
   }
   int i;
   for (i = 0 ; i < taille ; ++i)
   {
      mir[i] = str[taille - i - 1];
     /* le -1 est également important, sinon on commence à copier le
      * \0 et la chaîne mir paraît vide */
   }
   /* On oublie pas le \0 */
   mir[i] = '\0';
   return mir;
}


#define TAILLE_ALLOCATION 64
char *saisie(void)
{
   /* On va faire des allocations par blocs de TAILLE_ALLOCATION octets */
   int taille = TAILLE_ALLOCATION;
   char *s = malloc(taille);
   if (s == NULL)
   {
      perror("saisie(): malloc()");
      return NULL;
   }
   
   int i = 0;
   char c = getchar();

   while (!isspace(c))
   {
      if (i == (taille - 1)) /* Ici, j'utilise taille -1 pour être sûr
                            * de conserver de la place pour le \0 si
                            * je suis à la fin */
      {
         /* si on est au bout du tableau qu'on a alloué, on l'agrandi */
         taille += TAILLE_ALLOCATION;
         /* On sauvegarde le retour de realloc dans un pointeur
          * temporaire au cas où il y aurait une erreur */
         char *tmp = realloc(s, taille);
         if (tmp == NULL)
         {
            /* Si la réallocation échoue, on libère les ressources
             * allouées et on retourne une erreur.  On aurait
             * également pu choisir de retourner la chaîne qu'on a
             * réussit à construire. Dans ce cas, il faut penser à
             * ajouter un \0 avant (s[i-1] = '\0')
             */
            perror("saisie(): realloc");
            free(s);
            return NULL;
         }
         /* L'allocation s'est bien passée, on peut réaffecter le
          * pointeur */
         s = tmp;
      }
      s[i++] = c; /* i++ est post-incrémenté. Donc ce code est
                   * équivalent à s[i] = c; i++; */
      c = getchar();
   }
   /* On oublie pas de mettre un \0 */
   s[i] = '\0';
   /* et on réalloue à la taille exacte (attention au +1)! */
   char *tmp = realloc(s, i+1);
   if (tmp != NULL)
      s = tmp;
   /* Si la réallocation n'a pas marché, on peut quand même retourner
    * la chaîne qu'on a construite */
   return s;
}
