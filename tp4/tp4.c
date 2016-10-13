#include<stdio.h>
#include<string.h>
#include<stdlib.h>


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

int main(void)
{
  char *s = "fred";
  char *r = "derf";
  char *t = miroir(s);
  if(*r == *t) {
    printf("c'est ok \n");
  } 
  else {
    printf("ca marche pas \n");
  }
  return 1;
}
