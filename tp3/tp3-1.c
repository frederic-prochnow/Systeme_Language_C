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
  int size_s1 = mon_strlen2(s1);
  int size_s2 = mon_strlen2(s2);
  // CAS GENERAL : TAILLE EGAL
  if(size_s1 == size_s2) 
  {
    for(i=0; i<size_s1;i++){
      if(res == 0 && (s1[i] < s2[i]))
      {
        res = -2;   
      }
      if(res == 0 && (s1[i] > s2[i]))
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

int mon_strncmp(const char * s1, const char * s2, int n)
{
  int res = 0;
  int i;
  for(i=0; i<n;i++){
      if(res == 0 && (s1[i] < s2[i]))
      {
        res = -2;   
      }
      if(res == 0 && (s1[i] > s2[i]))
      {
        res = 2; 
      }
  }
  return res;  
}

char *mon_strcat(char *s1,const char *s2)
{
  int sizeof_s1 = mon_strlen2(s1);
  int sizeof_s2 = mon_strlen2(s2);
  int i;
  for(i=0; i<sizeof_s2; i++)
  {
    s1[sizeof_s1 + i] = s2[i];
    s1[sizeof_s1 + i +1] = '\0';
    printf("%i %s \n",i,s1);
  }
  s1[sizeof_s1+i] = '\0';
  printf("lol\n");
  return s1;
}

int main(void)
{
  char s[50] = "Hop !"; 
  char t[] = "Hop !!";
  char u[] = "salut !";
  printf("la chaine comporte %d elements \n",mon_strlen(s));
  printf("la chaine comporte %d elements \n",mon_strlen2(s));
  printf("s =>> %d -- t =>> %d \n",sizeof(s)-1,sizeof(t)-1);
  printf("le resultat devrait etre de 0 =>>> %d \n",mon_strcmp(s,s));
  printf("le resultat devrait etre de +1 =>> %d \n",mon_strcmp(t,s));
  printf("le resultat devrait etre de -1 =>> %d \n",mon_strcmp(s,t));
  printf("le resultat devrait etre de +2 =>> %d \n",mon_strcmp(s,u));
  printf("le resultat devrait etre de 0 =>>> %d \n",mon_strncmp(s,t,3));
  printf("le resultat devrait etre de 0 =>>> %d \n",mon_strncmp(s,t,5));
  printf("le resultat devrait etre de +2 =>> %d \n",mon_strncmp(s,u,5));
  printf("le resultat devrait etre de 0 =>>> %d \n",mon_strncmp(s,u,1));
  mon_strcat(s,u);
  printf(" s + t = <%s> soit une longeur de chaine de %d\n",s,mon_strlen2(s));
  return 0;
}
