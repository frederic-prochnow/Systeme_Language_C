#include <stdio.h>

int   mon_strlen(const char *s)
{
   int i;
   while (s[i++]);
   return i-1;
}
int   mon_strcmp(const char * s1, const char * s2)
{
   /* On parcours les deux chaînes tant que les caractères sont égaux 
      
      On ajoute en plus une condition d'arrêt sur *s1 pour détecter la
      fin d'une des deux chaînes.

      Tester la fin d'une des deux chaînes et suffisant:
      - Si les chaînes sont de même longueur, alors la fin de l'une implique la fin de l'autre
      - Si les chaînes sont de longueurs différentes, alors les
        caractères seront différents au plus tard à la fin de la plus
        courte.
    */
   for ( ; *s1 != '\0' && *s1 == *s2 ; s1++, s2++);
   /* Retourner la différence entre les deux caractères après la boucle suffit:

      - si les chaînes sont égales, le deux pointeurs pointent alors
        sur '\0', donc on retourne bien 0

      - sinon, on retourne la différence entre les premiers caractères
        différents ce qui donne bien une valeur négative ou positive
        en fonction de l'ordre lexicographique des deux chaînes
   */
   return *s1 - *s2;
}
int   mon_strncmp(const char * s1, const char * s2, int n)
{
   int i;
   /* Même fonction que précédemment avec un test de taile en plus */
   for ( i = 0 ; i < n && *s1 != '\0' && *s1 == *s2 ; s1++, s2++, i++);
   if (i == n) /* Si on quitte car i == n, alors on a trouvé */
      return 0;
   return *s1 - *s2;
}
char *mon_strcat(char *s1, const char *s2)
{
   char *p = s1; /* pour le retour */
   while (*s1++); /* on avance le pointeur s1 à la fin de la chaîne */
   while ((*s1++ = *s2++)); /* on copie s2 dans s1 */
   *s1 = '\0'; /* on oublie pas le '\0' */
   return p;
}
const char *mon_strchr(const char *s, int c)
{
   for ( ; *s != c && *s != '\0' ; s++);
   if (*s == c)
      return s;
   return NULL;
}

const char *mon_strstr(const char *haystack, const char *needle)
{
   int taille_needle = mon_strlen(needle);
   const char *p = haystack;
   while (*p) /* Tant qu'on est pas à la fin de haystack */
   {
      /* on cherche le premier caractère à partir de là ou on est arrivé */
      p = mon_strchr(p, needle[0]);
      if (p == NULL)
         return NULL;
      if (mon_strncmp(p, needle, taille_needle) == 0)
         return p; /* on a trouvé */
      p++; /* on cherche à partir du caractère suivant */
   }
   /* on a pas trouvé */
   return NULL;
}
