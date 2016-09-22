#include <stdio.h>

struct rat
{
  int den;
  int num;
};

struct rat rat_produit(struct rat n1, struct rat n2)
{
  struct rat res;
  res.den = n1.den*n2.den;
  res.num = n1.num*n2.num; 
  return res;
}

struct rat rat_somme(struct rat n1, struct rat n2)
{
 struct rat res;
 if(n1.num==n2.num)
 {
   res.den = n1.den+n2.den;
   res.num = n1.num;
 } 
 else
 {
   res.den = (n1.den*n2.num)+(n2.den*n1.num);
   res.num = n1.num*n2.num;
 }
 return res;

}

struct rat rat_plus_petit(struct rat list[])
{
  int i=0;
  float res_indice;
  float res_final;
  struct rat res;
  res.den =1;
  res.num =1;
  while(!list[i].den ==0)
  {
    /*
    //verification par numerateur
    if(list[i].num > res.num) 
    {
      res.den = list[i].den;
      res.num = list[i].num;
    }
    //verification par denominateur
    if(list[i].num == res.num && list[i].den < res.den)
    {
      res.den = list[i].den;
    }*/
    res_final = res.den/res.num;
    res_indice = list[i].den/list[i].num;
    if(res_indice < res_final)
    {
      res.den = list[i].den;
      res.num = list[i].num;
    }   
    i++;
  }
  return res;
}

int main(void)
{
  struct rat r1 ={1,2};
  struct rat r2 ={1,4};
  struct rat r3;
  struct rat r4;
  struct rat r5;
  printf("r1 =_____________ %d/%d \n",r1.den,r1.num);
  printf("r2 =_____________ %d/%d \n",r2.den,r2.num);
  r3 = rat_produit(r1,r2);
  printf("r1 X r2 = r3 =___ %d/%d \n",r3.den,r3.num);
  r4 = rat_somme(r1,r2);
  printf("r1 + r2 = r4 =___ %d/%d \n",r4.den,r4.num);
  r5 = rat_somme(r2,r3);
  printf("r2 + r3 = r5 =___ %d/%d \n",r5.den,r5.num);
  struct rat null = {0,0};
  struct rat liste[] = {r1,r2,r3,r4,r5,null};
  printf("nous mettons r1(%d/%d), r2(%d/%d), r3(%d/%d), r4(%d/%d), r5(%d/%d) dans une liste ... \n",
         liste[0].den,liste[0].num,liste[1].den,liste[1].num,liste[2].den,liste[2].num,
         liste[3].den,liste[3].num,liste[4].den,liste[4].num);
  struct rat res = rat_plus_petit(liste);
  printf("le plus petit est : %d/%d ! \n", res.den,res.num); 
  return 1;
}
