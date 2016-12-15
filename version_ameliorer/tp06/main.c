#include <stdio.h>
/* pour open */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "bmp.h"
#include "filtres.h"

int main(int argc, char **argv)
{

   if (argc < 3)
   {
      fprintf(stderr, "usage: %s [options] source destination\n", argv[0]);
      return 1;
   }

   const char *source = argv[argc-2];
   const char *destination = argv[argc-1];

   /* On charge le fichier source */
   image_bmp b;
   int fd_source;
   fd_source = open(source, O_RDONLY);
   if (fd_source == -1)
   {
      perror(source);
      return 2;
   }
   if (charger_bmp(fd_source, &b) == -1)
   {
      fprintf(stderr, "Chargement de %s impossible\n", source);
      return 3;
   }

   
   /* Application des filtres */

   /* Pour appliquer les filtres, on utilise getopt pour faciliter
    * l'analyse des options */
   int opt;
   while ((opt = getopt(argc, argv, "rnbsi")) != -1)
   {
      switch (opt)
      {
         case 'r': appliquer_filtre(&b, ROUGE); break;
         case 'n': appliquer_filtre(&b, NEGATIF); break;
         case 'b': appliquer_filtre(&b, NOIR_ET_BLANC); break;
         case 's': appliquer_filtre(&b, SUPERIEUR); break;
         case 'i': appliquer_filtre(&b, INFERIEUR); break;
         default:
            fprintf(stderr, "Option -%c inconnue. Option possibles: -r, -n, -b, -s, -i\n", opt);
            return 10;
      }
   }
   
   /* on ne crée le fichier destination que maintenant que le fichier
    * source est chargé et vérifié et que les filtres ont été
    * appliqués avec succès */
   
   int fd_destination = open(destination, O_WRONLY | O_TRUNC | O_CREAT, 0666);
   if (fd_destination == -1)
   {
      perror(destination);
      return 4;
   }
   /* Ecriture du fichier */
   if (sauver_bmp(fd_destination, &b) == -1)
   {
      fprintf(stderr, "Sauvegarde de %s impossible\n", destination);
      return 5;
   }
   return 0;
}
