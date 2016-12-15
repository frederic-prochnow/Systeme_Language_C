#ifndef __BMP_H__
#define __BMP_H__

/* On déclare des types dont on est sûr de la taille.
   Si on doit implémenter le TP sur une architecture différente, il
   suffit de changer ces déclarations
   En incluant le fichier stdint.h on aurait pu utiliser les types standard uint16_t et uint32_t
*/
typedef unsigned short uint16;
typedef unsigned int uint32;

typedef struct
{
   uint16 signature; /* doit être 0x4D42 */
   uint32 taille_fichier; /* Taille du fichier complet en octets */
   uint32 reserve; /* inutilisé mais doit être présent */
   uint32 offset_donnees; /* Nombre d'octets entre le début du fichier et le début des données de l'image */
} entete_fichier;

typedef struct
{
   uint32 taille_entete; /* Doit être au moins 40 */
   uint32 largeur;       /* largeur de l'image en pixel */
   uint32 hauteur;       /* hauteur de l'image en pixel */
   uint16 nombre_plans;  /* doit être à 1 */
   uint16 profondeur;    /* nombre de bit utilisés pour coder un pixel */
   uint32 compression;   /* Algorithme de compression utilisé */
   uint32 taille_donnees_image; /* nombre d'octets totaux utilisés pour coder les pixels de l'image, incluant les octets de bourrage */
   uint32 resolution_horizontale; /* en nombre de pixel par mètre */
   uint32 resolution_verticale;   /* en nombre de pixel par mètre */
   uint32 taille_palette;         /* en nombre de couleurs */
   uint32 nombre_de_couleurs_importantes; /* Nombre de couleur importants ou 0 quand elle le sont toutes. Souvent ignoré */
} entete_bitmap;

typedef struct
{
   entete_fichier fichier;
   entete_bitmap bitmap;
   unsigned char *pixels;
} entete_bmp;

typedef struct
{
   entete_bmp entete;
   unsigned char *pixels;
} image_bmp;

/** Charge un fichier bmp depuis le descripteur fd.

    @param fd le descripteur de fichier ouvert en lecture
    @param bmp l'adresse d'une structure image_bmp qui sera initialisée avec l'image contenue dans le fichier

    @return 0 si pas d'erreur, -1 sinon
*/
int charger_bmp(int fd, image_bmp *bmp);

/** Sauve l'image donnée en paramètre vers le descripteur fd

    @param fd le descripteur de fichier ouvert en écriture
    @param bmp l'adresse de la description d'un image VALIDE
*/
int sauver_bmp(int fd, const image_bmp *bmp);

#endif
