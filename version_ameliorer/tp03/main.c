#include <stdio.h>

#include "chaines.h"

const char *chaines[] = {
   "Toto",
   "Titi",
   "Bonjour",
   "Tata",
   "jouet",
   NULL
};

int main(void)
{
   const char *s = "Bonjour le monde!";

   printf("Taille de \"%s\": %d\n", s, mon_strlen(s));

   int i, j;
   for (i = 0 ; chaines[i] != NULL ; ++i)
   {
      for (j = 0 ; chaines[j] != NULL ; ++j)
         printf("Comparaison de \"%s\" et \"%s\": %d\n", chaines[i], chaines[j], mon_strcmp(chaines[i], chaines[j]));
   }

   for (i = 0 ; chaines[i] != NULL ; ++i)
   {
      const char *p = mon_strchr(chaines[i], 'o');
      if (p)
         printf("Recherche de 'o' dans \"%s\": \"%s\"\n", chaines[i], p);
      else
         printf("Recherche de 'o' dans \"%s\": non trouvé\n", chaines[i]);
   }


   for (i = 0 ; chaines[i] != NULL ; ++i)
   {
      const char *p = mon_strstr(chaines[i], "jou");
      if (p)
         printf("Recherche de \"jou\" dans \"%s\": \"%s\"\n", chaines[i], p);
      else
         printf("Recherche de \"jou\" dans \"%s\": non trouvé\n", chaines[i]);
   }

   
   return 0;
}
