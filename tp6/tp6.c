#include <stdio.h>

/*
 lit deux octets dans le fichier dont le descripteur est donne en parametre et retourne le nombre d’octets effectivement
 lus, -1 en cas d’erreur et 0 si le fichier est terminé.
*/
int lire_deux_octets(int fd, uint16 *val) {
  if(/*fd = numero de la signature dans la structure entete_fichier*/) {
    return /*nombre d'octets lus*/
  } else {
    // ERREUR
    return -1;
  } return 0;
}

/*
 lit quatre octets dans le fichier dont le descripteur est donne en parametre et retourne le nombre d’octets effectivement
 lus, -1 en cas d’erreur et 0 si le fichier est terminé.
*/
int lire_quatre_octets(int fd, uint32 *val) {
  return 0;
}

/*
 lit l’entete du fichier en entree et stocke les informations dans la structure passee en parametre en se servant des
 fonctions precedentes. La fonction doit retourner -1 si l’entete n’a pas pu etre lue correctement
*/
int lire_entete(int de, entete_bmp *entete) {
  return 0;
}
