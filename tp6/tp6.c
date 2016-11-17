#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "structure.h"

/*
lit deux octets dans le fichier dont le descripteur est donne en parametre et retourne le nombre d’octets effectivement lus, -1 si il y a une erreur ou  0 si le fichier est terminé.
*/
int lire_deux_octets(int openFile, uint16 *val) {
  char buffer [2];
  int i;
  int readFile = read(openFile,buffer,2);
  if(readFile == -1) return -1;
  if(readFile ==  0) return 0;
  for(i=0;i<2;i++){
    val += buffer[i]<<(8*i);
  } 
  return readFile;
}

/*
lit quatre octets dans le fichier dont le descripteur est donne en parametre et retourne le nombre d’octets effectivement lus, 0 si le fichier est terminé.
*/
int lire_quatre_octets(int openFile, uint32 *val) {
  char buffer[4];
  int i;
  int readFile = read(openFile,buffer,4);
  if(readFile == -1) return -1;
  if(readFile == 0) return 0;
  for(i=0;i<4;i++){
    val += buffer[i]<<(8*i);
  }
  return readFile;
}

/*
lit l’entete du fichier en entree et stocke les informations dans la structure passee en parametre en se servant des fonctions precedentes. La fonction doit retourner -1 si l’entete n’a pas pu etre lue correctement
*/
int lire_entete(int openFile, entete_bmp *entete) {
  lire_deux_octets(openFile,&entete->fichier.signature);
  lire_quatre_octets(openFile,&entete->fichier.taille_fichier);
  lire_quatre_octets(openFile,&entete->fichier.reserve);
  lire_quatre_octets(openFile,&entete->fichier.offset_donnees);
  lire_quatre_octets(openFile,&entete->bitmap.taille_entete);
  lire_quatre_octets(openFile,&entete->bitmap.largeur);
  lire_quatre_octets(openFile,&entete->bitmap.hauteur);
  lire_deux_octets(openFile,&entete->bitmap.nombre_plans);
  lire_deux_octets(openFile,&entete->bitmap.profondeur);
  lire_quatre_octets(openFile,&entete->bitmap.compression);
  lire_quatre_octets(openFile,&entete->bitmap.taille_donnees_image);
  lire_quatre_octets(openFile,&entete->bitmap.resolution_horizontale);
  lire_quatre_octets(openFile,&entete->bitmap.resolution_verticale);
  lire_quatre_octets(openFile,&entete->bitmap.taille_palette);
  lire_quatre_octets(openFile,&entete->bitmap.nombre_de_couleurs_importantes);
  printf("entete->fichier.signature :___________________ %d\n",entete->fichier.signature);
  printf("entete->fichier.taille_fichier :______________ %d\n",entete->fichier.taille_fichier);
  printf("entete->fichier.reserve :_____________________ %d\n",entete->fichier.reserve);
  printf("entete->fichier.offset_donnees :______________ %d\n",entete->fichier.offset_donnees);
  printf("entete->bitmap.taille_entete :________________ %d\n",entete->bitmap.taille_entete);
  printf("entete->bitmap.largeur :______________________ %d\n",entete->bitmap.largeur);
  printf("entete->bitmap.hauteur :______________________ %d\n",entete->bitmap.hauteur);
  printf("entete->bitmap.nombre_plans :_________________ %d\n",entete->bitmap.nombre_plans);
  printf("entete->bitmap.profondeur :___________________ %d\n",entete->bitmap.profondeur);
  printf("entete->bitmap.compression :__________________ %d\n",entete->bitmap.compression);
  printf("entete->bitmap.taille_donnees_image :_________ %d\n",entete->bitmap.taille_donnees_image);
  printf("entete->bitmap.resolution_horizontale :_______ %d\n",entete->bitmap.resolution_horizontale);
  printf("entete->bitmap.resolution_verticale :_________ %d\n",entete->bitmap.resolution_verticale);
  printf("entete->bitmap.taille_palette :_______________ %d\n",entete->bitmap.taille_palette);
  printf("entete->bitmap.nombre_de_couleurs_importantes : %d\n",entete->bitmap.nombre_de_couleurs_importantes);



  return 0;
}

//int ecrire_deux_octets(int fd, uint16 val){}
/* écrit deux octets dans le fichier dont le descripteur est donné en paramètre et retourne le nombre d’octets effectivement
écrits ou -1 si une erreur est survenue.*/

//int ecrire_quatre_octets(int fd, uint32 val){}
/* écrit quatre octets dans le fichier dont le descripteur est donné en paramètre et retourne le nombre d’octets
effectivement écrits ou -1 si une erreur est survenue.*/

//int ecrire_entete(int vers, entete_bmp *entete){}
/*qui écrit l’entete passée en paramètre dans le fichier de destination en se servant des fonctions précédentes. La fonction
doit retourner -1 si l’entête n’a pas pu être lue correctement.*/

int main(void){
   int openFile = open("bmptest01.bmp",O_RDONLY);
   entete_bmp *entete; 
   lire_entete(openFile,entete);
   return 0;
}
