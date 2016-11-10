#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
lit deux octets dans le fichier dont le descripteur est donne en parametre et retourne le nombre d’octets effectivement lus, -1 si il y a une erreur ou  0 si le fichier est terminé.
*/
int lire_deux_octets(int openFile, uint16 *val) {
  char buffer [2];
  openFile = read(openFile,buffer,2);
  if(openFile == -1) return -1;
  if(openFile == 0) return 0;
  int x = buffer[0] <<8;
  int y = buffer[1];
  val = x+y;
  return val;
}

/*
lit quatre octets dans le fichier dont le descripteur est donne en parametre et retourne le nombre d’octets effectivement lus, 0 si le fichier est terminé.
*/
int lire_quatre_octets(int openFile, uint32 *val) {
  char buffer[4];
  openFile = read(openFile,buffer,4);
  if(openFile == -1) return -1;
  if(openFile == 0) return 0;
  int w = buffer[0] <<24;
  int x = buffer[1] <<16;
  int y = buffer[2] <<8;
  int z = buffer[3];
  val = w+x+y+z;
  return val;
}

/*
lit l’entete du fichier en entree et stocke les informations dans la structure passee en parametre en se servant des fonctions precedentes. La fonction doit retourner -1 si l’entete n’a pas pu etre lue correctement
*/
int lire_entete(int de, entete_bmp *entete) {
  return 0;
}
