#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include <unistd.h>

#include "bmp.h"

/* Les valeurs attendues */
#define SIGNATURE_BMP     0x4D42
#define TAILLE_ENTETE_BMP     40
#define NB_PLANS_BMP           1


/* Les fonction outils.
   Toutes ces fonctions ne sont utilisées que dans ce fichier .c

   On utilise donc le mot clé statique, pour les rendre inaccessible
   depuis d'autres fichiers .c

   Ce n'est pas obligatoire, mais c'est plus propre.
*/
static int lire_deux_octets(int fd, uint16 *val)
{
   /* On lit deux octets, on les range dans la variable pointée par
    * val et on retourne le nombre d'octets lus */
   return read(fd, val, 2);
}

static int lire_quatre_octets(int fd, uint32 *val)
{
   /* On lit quatre octets, on les range dans la variable pointée par
    * val et on retourne le nombre d'octets lus */
   return read(fd, val, 4);
}

static int ecrire_deux_octets(int fd, uint16 val)
{
   /* on écrit les deux octets de la variable val dans le fichier */
   return write(fd, &val, 2);
}

static int ecrire_quatre_octets(int fd, uint32 val)
{
   /* on écrit les deux octets de la variable val dans le fichier */
   return write(fd, &val, 4);
}


/* Le chargement de l'entête */
static int lire_entete(int fd, entete_bmp *entete)
{
   /* On commence par se placer au début du fichier */
   if (lseek(fd, 0, SEEK_SET) == -1)
   {
      perror("lire_entete(): lseek()");
      return -1;
   }
   /* on lit l'entete */
   int n = 0;
   /* La partie entête de fichier */
   n += lire_deux_octets(fd, &(entete->fichier.signature));
   n += lire_quatre_octets(fd, &(entete->fichier.taille_fichier));
   n += lire_quatre_octets(fd, &(entete->fichier.reserve));
   n += lire_quatre_octets(fd, &(entete->fichier.offset_donnees));
   /* si on a pas lu le nombre d'octets nécessaire, c'est une erreur */
   if (n != 14)
   {
      perror("lire_entete(): partie fichier");
      return -1;
   }
   /* On continue avec la partie bitmap */
   n = 0;
   n += lire_quatre_octets(fd, &(entete->bitmap.taille_entete));
   n += lire_quatre_octets(fd, &(entete->bitmap.largeur));
   n += lire_quatre_octets(fd, &(entete->bitmap.hauteur));
   n += lire_deux_octets(fd, &(entete->bitmap.nombre_plans));
   n += lire_deux_octets(fd, &(entete->bitmap.profondeur));
   n += lire_quatre_octets(fd, &(entete->bitmap.compression));
   n += lire_quatre_octets(fd, &(entete->bitmap.taille_donnees_image));
   n += lire_quatre_octets(fd, &(entete->bitmap.resolution_horizontale));
   n += lire_quatre_octets(fd, &(entete->bitmap.resolution_verticale));
   n += lire_quatre_octets(fd, &(entete->bitmap.taille_palette));
   n += lire_quatre_octets(fd, &(entete->bitmap.nombre_de_couleurs_importantes));

   /* Si on a pas lu le nombre d'octets attendu */
   if (n < TAILLE_ENTETE_BMP)
   {
      if (errno != 0) /* si errno est non nul, il s'agit d'une erreur de lecture dans le fichier */
         perror("lire_entete(): partie bitmap");
      else /* sinon, c'est que le fichier bitmap est corrompu (taille_entete est mauvais) */
         fprintf(stderr, "lire_entete(): partie bitmap: taille_entete non valide: %d octets lu, %u attendus\n", n, entete->bitmap.taille_entete);
      return -1;
   }
   return 0;
}

/* Ecriture de l'entete */
static int ecrire_entete(int fd, const entete_bmp *entete)
{
   /* On commence par se placer au début du fichier */
   if (lseek(fd, 0, SEEK_SET) == -1)
   {
      perror("lire_entete(): lseek()");
      return -1;
   }
   /* on écrit l'entete */
   int n = 0;
   /* La partie entête de fichier */
   n += ecrire_deux_octets(fd, entete->fichier.signature);
   n += ecrire_quatre_octets(fd, entete->fichier.taille_fichier);
   n += ecrire_quatre_octets(fd, entete->fichier.reserve);
   n += ecrire_quatre_octets(fd, entete->fichier.offset_donnees);
   /* si on a pas écrit le nombre d'octets nécessaire, c'est une erreur */
   if (n != 14)
   {
      perror("ecrire_entete(): partie fichier");
      return -1;
   }
   /* On continue avec la partie bitmap */
   n = 0;
   n += ecrire_quatre_octets(fd, entete->bitmap.taille_entete);
   n += ecrire_quatre_octets(fd, entete->bitmap.largeur);
   n += ecrire_quatre_octets(fd, entete->bitmap.hauteur);
   n += ecrire_deux_octets(fd, entete->bitmap.nombre_plans);
   n += ecrire_deux_octets(fd, entete->bitmap.profondeur);
   n += ecrire_quatre_octets(fd, entete->bitmap.compression);
   n += ecrire_quatre_octets(fd, entete->bitmap.taille_donnees_image);
   n += ecrire_quatre_octets(fd, entete->bitmap.resolution_horizontale);
   n += ecrire_quatre_octets(fd, entete->bitmap.resolution_verticale);
   n += ecrire_quatre_octets(fd, entete->bitmap.taille_palette);
   n += ecrire_quatre_octets(fd, entete->bitmap.nombre_de_couleurs_importantes);

   /* Si on a pas écrit le nombre d'octets attendu */
   if (n < TAILLE_ENTETE_BMP)
   {
      if (errno != 0) /* si errno est non nul, il s'agit d'une erreur d'écriture dans le fichier */
         perror("ecrire_entete(): partie bitmap");
      else /* sinon, c'est qu'il y a un problème avec les valeurs de l'entete */
         fprintf(stderr, "ecrire_entete(): partie bitmap: taille_entete non valide: %d octets écrits, %u annoncés\n", n, entete->bitmap.taille_entete);
      return -1;
   }
   return 0;
}


static int verifier_entete(const entete_bmp *entete)
{
   if (entete->fichier.signature != SIGNATURE_BMP)
   {
      fprintf(stderr, "Signature invalide\n");
      return 0;
   }
   if (entete->bitmap.profondeur != 24)
   {
      fprintf(stderr, "Image de profondeur %u, seule la profondeur 24 bits est gérée\n", entete->bitmap.profondeur);
      return 0;
   }
   if (entete->bitmap.taille_entete < TAILLE_ENTETE_BMP)
   {
      fprintf(stderr, "Taille de l'entete invalide: %u lu, %d minimum attendu\n", entete->bitmap.taille_entete, TAILLE_ENTETE_BMP);
      return 0;
   }
   if (entete->bitmap.nombre_plans != NB_PLANS_BMP)
   {
      fprintf(stderr, "Nombre de plans invalide: %u lu, %d attendu\n", entete->bitmap.nombre_plans, NB_PLANS_BMP);
      return 0;
   }
   return 1;
}


static unsigned char *allouer_pixels(const entete_bmp *entete)
{
   return malloc(entete->bitmap.taille_donnees_image);
}

static int lire_pixels(int fd, const entete_bmp *entete, unsigned char *pixels)
{
   /* On commence par se placer au bon endroit dans le fichier */
   if (lseek(fd, entete->fichier.offset_donnees, SEEK_SET) == -1)
   {
      perror("lire_pixels: lseek");
      return -1;
   }
   return read(fd, pixels, entete->bitmap.taille_donnees_image);
}

static int ecrire_pixels(int fd, const entete_bmp *entete, unsigned char *pixels)
{
   /* On commence par se placer au bon endroit dans le fichier destination.
      Si lseek déplace le curseur après la fin du fichier, le nombre
      nécessaire de 0 sera écrit avant la première écriture demandée
   */
   if (lseek(fd, entete->fichier.offset_donnees, SEEK_SET) == -1)
   {
      perror("ecrire_pixels: lseek");
      return -1;
   }
   return write(fd, pixels, entete->bitmap.taille_donnees_image);
}


int charger_bmp(int fd, image_bmp *bmp)
{
   if (lire_entete(fd, &bmp->entete) == -1)
      return -1;
   if (!verifier_entete(&bmp->entete))
      return -1;
   bmp->pixels = allouer_pixels(&bmp->entete);
   if (bmp->pixels == NULL)
   {
      perror("charger_bmp: allouer_pixel");
      return -1;
   }
   if (lire_pixels(fd, &bmp->entete, bmp->pixels) != (int) bmp->entete.bitmap.taille_donnees_image)
   {
      fprintf(stderr, "charger_bmp: erreur dans la lecture des pixels, fichier tronqué ?\n");
      return -1;
   }
   return 0;
}
int sauver_bmp(int fd, const image_bmp *bmp)
{
   if (ecrire_entete(fd, &bmp->entete) == -1)
      return -1;
   if (ecrire_pixels(fd, &bmp->entete, bmp->pixels) == -1)
      return -1;
   return 0;
}
