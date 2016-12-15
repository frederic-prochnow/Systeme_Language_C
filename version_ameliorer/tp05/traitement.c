#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

#define BUFF_SIZE 1024

int traiter(int fd, int *car, int *lig, int *mot)
{
   char buffer[BUFF_SIZE];
   char old = ' '; /* On se sert de cette variable pour le comptage de mots */
   int s;
   *car = 0;
   *mot = 0;
   *lig = 0;
   while ((s = read(fd, buffer, BUFF_SIZE)) > 0)
   {
      *car += s; /* Pas besoin d'ajouter 1 à chaque tour du for */
      for (int i = 0 ; i < s ; ++i)
      {
         
         if (buffer[i] == '\n') /* Une ligne est comptée seulement si on a \n */
            (*lig)++;
         /* On compte un mot supplémentaire quand le caractère
          * précédent n'est pas un alpha numérique et que le courant
          * est alpha numérique */
         if (!isalnum(old) && isalnum(buffer[i]))
            (*mot)++;
         /* on retient le caractère courant qui devient le caractère
          * précédent du tour de boucle suivant y compris dans la prochain tour de read */
         old = buffer[i];
      }
   }
   if (s == -1)
   {
      perror("traiter: read");
      return -1;
   }
   return 0;
}

