#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/**
* W C
*/

int cptCaractere(char * f)
{
 int compteur = 0;
 int i = 0;
 int openFile = open(f,O_RDONLY);
 int readFile;
 char *  buffer; 
 if (openFile == -1)
  perror("Erreur à l'ouverture du fichier");
 
 else {
    readFile = read(openFile,buffer,100);
    while(!(readFile < 100)){
       compteur += readFile;
       //printf("----nb : %d -- readFile : %d\n",compteur,readFile);
       readFile = read(openFile,buffer,100);
     }
     compteur += readFile;
 }
 close(openFile);
 return compteur;
}

int cptMot(char * f)
{
  int compteur = 0;
  int i = 0;
  int openFile = open(f,O_RDONLY);
  int readFile;
  char * buffer; 
  if(openFile == -1)
   perror("Erreur l'ouverture du fichier");

  else {
    readFile = read(openFile,buffer,100);
    while(!(readFile <100)) {
      for(i=0; i<readFile; i++) {
        if(buffer[i] == ' ' || buffer[i] == '\n'){
          compteur ++;
        }
      }
      readFile = read(openFile,buffer,100);
    }
    compteur += readFile;
  }
  close(openFile);
  return compteur;
}

int cptLigne(char * f)
{
  int compteur = 0;
  int i = 0;
  int openFile = open(f,O_RDONLY);
  int readFile;
  char * buffer;
  if(openFile == -1)
   perror("Erreur l'ouverture du fichier");
 
  else {
     readFile = read(openFile,buffer,100);
     while(!(readFile < 100)) {
       for(i=0; i<readFile; i++) {
          if(buffer [i] == '\n')
            compteur ++;
       }
     readFile = read(openFile,buffer,100);  
    }
    compteur += readFile;
  }
  close(openFile);
  return compteur;
}

int main(int argc,char *argv[])
{
 int i;
 int j;
 int c = 0;
 int w = 0;
 int l = 0;
 int res = 0;
 if(argc <= 1) {
    printf("\nLe Programme n'a reçu aucun argument\n");
  } else {
     for(i = 1; i< argc; i++) {
       if(argv[i] [0] == '-') {
         for(j=1; j<strlen(argv[i]); j++) {
            switch(argv[i] [j]) {
               case 'c' : c = 1; break;
               case 'w' : w = 1; break;
               case 'l' : l = 1; break;
               default : res = -1; break;
            }
          }
       	} else {
          if(c == 1){
            printf("nb caractere : %d --> %s\n",cptCaractere(argv[argc-1]),argv[argc-1]);
	  }
          if(w == 1){
            printf("nb mot : %d --> %s\n",cptMot(argv[argc-1]),argv[argc-1]);

          }
          if(l == 1){
            printf("nb ligne : %d --> %s\n",cptLigne(argv[argc-1]),argv[argc-1]);          
          }
          if(res == -1){
            printf("ERREUR");
          }
        }
    }
  }
  return 1; 
}
