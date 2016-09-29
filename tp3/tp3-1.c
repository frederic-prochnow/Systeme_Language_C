#include<stdio.h>
#include<string.h>

int mon_strlen(char s[])
{
  int i =0;
  int cpt =0;
  int boolean =1;
  while(boolean == 1)
  {
    if(s[i]!='\0')
    {
      cpt++;
      i++;
    } 
    else
    {
      boolean =0;
    }
  }
  return cpt;
}

int mon_strlen2(const char *s)
{
 int i =0;
 int cpt =0;
 int boolean =1;
 while(boolean == 1)
 {
   if(*(s+i)!='\0')
   {
     cpt++;
     i++;
   }
   else
   {
     boolean =0;
   }
 }
 return cpt;
}

int mon_strcmp(const char * s1,const char * s2)
{
  int res = 0;
  int i;
  int ascii_s1;
  int ascii_s2;
  int size_s1 = sizeof(s1)-1;
  int size_s2 = sizeof(s2)-1;
  // CAS GENERAL : TAILLE EGAL
  if(size_s1 == size_s2) 
  {
    for(i=0; i<size_s1;i++){
      ascii_s1 = (int) s1[i];
      ascii_s2 = (int) s2[i];
      if(res == 0 && ascii_s1 < ascii_s2)
      {
        res = -2;   
      }
      if(res == 0 && ascii_s2 > ascii_s2)
      {
        res = 2; 
      }
    }
  } 
  // CAS DE CHAINE DE TAILLE DIFFERENTE
  else
  {
    if(size_s1 < size_s2)
    {
      res = -1; 
    } 
    if(size_s1 > size_s2)
    {
      res = 1;
    }
  }
  return res;
}

int main(void)
{
  char s[] = "Hop !"; 
  char t[] = "Hop !!";
  printf("la chaine comporte %d elements \n",mon_strlen(s));
  printf("la chaine comporte %d elements \n",mon_strlen2(s));
  printf("s =>> %d -- t =>> %d \n",sizeof(s),sizeof(t));
  printf("le resultat devrait etre de 0 =>>> %d \n",mon_strcmp(s,s));
  printf("le resultat devrait etre de +1 =>> %d \n",mon_strcmp(t,s));
  printf("le resultat devrait etre de -1 =>> %d \n",mon_strcmp(s,t));
  return 0;
}
