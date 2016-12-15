#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int traiter(int fd, int *car, int *lig, int *mot);

int verif_option(const char *option, int *c, int *l, int *w)
{
   if (option[0] != '-')
      return 0; /* pas une option */
   option++;
   for ( ; *option != '\0'; ++option)
   {
      switch (*option)
      {
         case 'c': *c = 1; break;
         case 'w': *w = 1; break;
         case 'l': *l = 1; break;
         default:
            return -1;
      }
   }
   return 1;
}

void afficher_resultat(const char *nom, int car, int lig, int mot, int c, int l, int w)
{
   if (c)
      printf("caracteres : %d ", car);
   if (l)
      printf("lignes : %d ", lig);
   if (w)
      printf("mots : %d ", mot);
   printf("--> %s\n", nom);
}

int traiter_options(int argc, char **argv, int *c, int *w, int *l)
{
   int i;
   /* on vérifie les options */
   for ( i = 1  ; i < argc ; ++i)
   {
      const int v = verif_option(argv[i], c, l, w);
      /* option inconnue */
      if (v == -1)
      {
         fprintf(stderr, "option %s invalide\n", argv[i]);
         return -1;
      }
      /* fin des options, i contient l'indice du premier fichier à traiter */
      if (v == 0)
         break;
   }
   /* sans option, on affiche tout */
   if (*c == 0 && *l == 0 && *w == 0)
      *c = *l = *w = 1;
   return i;
}

int main(int argc, char **argv)
{
   int c = 0 , l = 0 , w = 0;
   int charac=0, lines=0, words=0;

   const int idx_fichier = traiter_options(argc, argv, &c, &w, &l);
   if ( idx_fichier == -1 )
      return 1;
   
   /* Sans nom de fichier, on traite l'entrée standard */
   if (idx_fichier == argc)
   {
      if (traiter(0, &charac, &lines, &words) == -1)
         return 1;
      afficher_resultat("stdin", charac, lines, words, c, l, w);
      return 0;
   }
   int success = 0; /* on passera cette variable à 1 si on parvient à traiter un fichier. */
   /* Ce flag nous indique si on a traité qu'un seul fichier
      pour savoir si on doit afficher le total */
   const int only_one = (idx_fichier == (argc - 1));
   int sum_c = 0, sum_l = 0, sum_w = 0;
   /* on traite les fichier */
   for (int i = idx_fichier ; i < argc ; ++i)
   {
      const int fd = open(argv[i], O_RDONLY);
      if (fd == -1)
      {
         /* Si on arrive pas à ouvrir le fichier, on affiche une erreur et on passe au suivant */
         perror(argv[i]);
         continue;
      }
      if (traiter(fd, &charac, &lines, &words) == -1)
      {
         close(fd);
         continue; /* on passe au suivant */
      }
      sum_c += charac;
      sum_l += lines;
      sum_w += words;
      afficher_resultat(argv[i], charac, lines, words, c, l, w);
      success = 1;
      close(fd);
   }
   if (!success)
      return 1; /* si on a pas reussi à traiter un fichier, on quitte avec une erreur */
   if (!only_one) /* on affiche le total si nécessaire */
      afficher_resultat("total", sum_c, sum_l, sum_w, c, l, w);;
   return 0;
}
