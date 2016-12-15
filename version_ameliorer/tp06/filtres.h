#ifndef __FILTRES_H__
#define __FILTRES_H__

#include "bmp.h"

typedef enum {
   ROUGE,
   NOIR_ET_BLANC,
   NEGATIF,
   SUPERIEUR,
   INFERIEUR,
} filtre_t;



/** Applique un filtre donné à une image.

    Modifie l'image ainsi que son entête si nécessaire

    @param image l'image à modifier
    @param filtre le filtre à appliquer

    @return -1 en cas d'erreur, 0 sinon
*/
int appliquer_filtre(image_bmp *image, filtre_t filtre);

#endif
