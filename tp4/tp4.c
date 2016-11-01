#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <ctype.h>


char * miroir (const char *s)
{
  char *u = malloc(strlen(s)*sizeof(char));
  if(u == "null") {
     return "null";
  } else {
    int i = 0;
    while (i<strlen(s))
    {
      u[i] = s[strlen(s)-i-1];
      i++; 
    }
    return u;
  }
}

char * saisie ()
{
  char *chaine = malloc(sizeof(char));
  char c;
  int cpt=0;
  do{
    chaine = realloc(chaine,cpt+2);
    c=getchar();
    *(chaine+cpt)=c;
    cpt++;
  }while(!isspace(c)); 
  return chaine;
}

int main(int argc,char *argv[])
{
  int i;
  int j;
  int im = 0;
  int is = 0;
  int res = 0;
  if(argc <= 1) {
    printf("\nLe Programme n'a recu aucun argument\n");
  } else {
     for(i = 1; i< argc; i++) {
       if(argv[i] [0] == '-') {
         for(j=1; j<strlen(argv[i]); j++) {
            switch(argv[i] [j]) {
               case 'm' : im = 1; break;
               case 's' : is = 1; break;
               default : res = -1; break;
            }
          }
       }
       else {
	 if(    im == 1 && is == 0){
	   printf("%s\n",miroir(argv[i])); 
	   im--;
	 }
	  
	 else if(im == 0 && is == 1) {
	   printf("%s\n",saisie());
	   is--;
	 }
	 else if(im == 1 && is == 1){
	   char * res = saisie();
	   printf("%s%s\n",res,miroir(res));
	   im--;
	   is--;
	 }
	 else if (res == -1) printf("\n ERREUR !!!\n");
	 else printf("\n ERREUR !!!\n");
       }
     }
  }
}
