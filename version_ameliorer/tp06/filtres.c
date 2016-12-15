#include <string.h>
#include "filtres.h"

/* Macro qui retourne vrai si le filtre ne touche qu'aux pixels
 * indépendamment les uns des autres */
#define FILTRE_PIXEL(f) ((f) <= NEGATIF)
#define FILTRE_MOITIE(f) ((f) > NEGATIF && (f) <= INFERIEUR)

/** Retourne la taille en octet d'une ligne avec ou sans compter le padding */
static int taille_ligne(const entete_bmp *entete, int avec_padding)
{
   int tl = (entete->bitmap.profondeur >> 3) * entete->bitmap.largeur;
   int mod = 4 - (tl % 4);
   if (mod != 4 && avec_padding)
      tl += mod;
   return tl;
}

static int appliquer_filtre_pixel(image_bmp *image, filtre_t filtre)
{
   /* Cette fonction ne marche que pour les filtres pixels */
   if (!FILTRE_PIXEL(filtre))
      return -1;
   /* Cette fonction se charge d'appliquer un filtre de type pixel. 
      Elle parcours les pixels un à un et les modifies en fonction du filtre
   */
   /* On récupère la taille de ligne qui inclue les octets de padding */
   int tlp = taille_ligne(&image->entete, 1);
   /* ET la taille sans ces octets */
   int tl = taille_ligne(&image->entete, 0);
   
   /* Dans cette fonction, on se déplace de ligne en ligne.  Pour
      cela, on utilise un pointeur p qui pointe toujours vers le début
      de la ligne en cours.
   */
   unsigned char *p = image->pixels;
   /* A chaque ligne, on avance le pointeur p de la taille d'une ligne padding compris (en octets) */
   for (unsigned int ligne = 0 ; ligne < image->entete.bitmap.hauteur ; ligne++, p += tlp )
   {
      /* On ne traite pas les octets de padding, on peut s'arrête à tl */
      for (int pixel = 0 ; pixel < tl ; pixel += 3)
      {
         switch (filtre)
         {
            case ROUGE:
               /* Pour passer notre image en rouge, on ne conserve que
                * la composante rouge. On aurait pu également calculer
                * la luminance du pixel et ne l'appliquer qu'au
                * rouge. L'effet aurait été différent. */
               p[pixel] = 0;   /* bleu */
               p[pixel+1] = 0; /* vert */
               /* rouge inchangé */
               break;
            case NOIR_ET_BLANC:
            {
               /* On calcule la luminance du pixel et on l'affect à
                toutes les composantes de couleur.  On utilise la
                moyenne pondérée des couleur en suivant la
                recommandation UIT-R BT 709.  On aurait simplement pu
                faire une moyenne non pondérée, le rendu aurait été
                noir et blanc mais respectant moins la luminosité
                resentie de l'image
               */
               float lum;
               lum  = 0.0722 * p[pixel];   /* bleu */
               lum += 0.7152 * p[pixel+1]; /* vert */
               lum += 0.2126 * p[pixel+2]; /* rouge */
               p[pixel] = p[pixel+1] = p[pixel+2] = (unsigned char) lum;
            }
            break;
            case NEGATIF:
               /* On prend simplement le complément à 1 de chaque composante */
               p[pixel]   = ~p[pixel];
               p[pixel+1] = ~p[pixel+1];
               p[pixel+2] = ~p[pixel+2];
               break;
            default:
               return -1; /* Cas normalement non atteint, grâce au test de début de fonction */
         }
      }
   }
   return 0;
}

static int moitie(image_bmp *image, int superieur)
{
   /* On recalcule tous les champs nécessaires:

      - la hauteur, il faut diviser le nombre de ligne par 2. C'est
        notre point de départ pour recalculer le reste }
      - la taille des données de l'image = nouvelle hauteur * taille d'une ligne (padding compris)
      - la taille du fichier: offset donnees image + taille donnees image
   */
   unsigned int ancienne_hauteur =    image->entete.bitmap.hauteur; /* on sauvegarde pour après */
   unsigned int tlp = taille_ligne(&image->entete, 1); /* la taille de ligne padding compris */
   image->entete.bitmap.hauteur /= 2;
   image->entete.bitmap.taille_donnees_image =  tlp * image->entete.bitmap.hauteur;
   image->entete.fichier.taille_fichier = image->entete.bitmap.taille_donnees_image + image->entete.fichier.offset_donnees;
   /* Si on veut la partie inférieure, ça suffit, on sauvera juste les lignes nécessaires. */
   if (!superieur)
      return 0;
   
   /* Sinon, il faut recopier les premières lignes en tête des données 
      On calcule l'offset de la ligne du milieu et on recopie les pixels de cet offset au début du tableau
   */
   unsigned int offset = (ancienne_hauteur - image->entete.bitmap.hauteur) * tlp;
   memcpy(image->pixels, image->pixels + offset, image->entete.bitmap.hauteur * tlp);
   return 0;
}

int appliquer_filtre(image_bmp *image, filtre_t filtre)
{
   if (FILTRE_PIXEL(filtre))
      return appliquer_filtre_pixel(image, filtre);
   if (FILTRE_MOITIE(filtre))
      return moitie(image, filtre == SUPERIEUR);
   return -1;
}
