#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <ctype.h>


char * miroir (const char *s)
{
  char *u = malloc(strlen(s)*sizeof(char));
  if(u == NULL) {
     printf("ERREUR MIROIR /n");
     return NULL;
  } else {
    int i = 0;
    int len = strlen(s);
    while (i<len)
    {
      u[i] = s[len-i-1];
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
  int len;
  int im = 0;
  int is = 0;
  int res = 0;
  char erreur;
  if(argc <= 1) {
    printf("\nLe Programme n'a recu aucun argument\n");
  } else {
     for(i = 1; i< argc; i++) {
       if(argv[i] [0] == '-') {
          len = strlen(argv[i]);
          for(j=1; j<len; j++) {
            switch(argv[i] [j]) {
               case 'm' : im = 1; break;
               case 's' : is = 1; break;
               default  :res = -1 ;erreur = argv[i][j]; break;
            }
          }
          if(res != -1 && i<argc && im == 1 && is == 0 )
            printf ("ERREUR MIROIR\n");
          if(res != -1 && im == 0 && is == 1 ) {
            printf("%s\n",saisie());
            is--;
          }
          if(res != -1 && i<argc && im == 1 && is == 1 ) {
            char * res = saisie();
            printf("%s%s\n",res,miroir(res));
            im--; is--;
          }
          if( res == -1) {
            printf ("-%c >> ERREUR ARGUMENT(S)\n",erreur);
          }

         }else {
	  if(res != -1 && im == 1 && is == 0){
	   printf("%s\n",miroir(argv[i])); 
	   im--;
	 }
	  if (res == -1) printf("\n ERREUR !!!\n");
        }
     }
  }
  return 0;
}
