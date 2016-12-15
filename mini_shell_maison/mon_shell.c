#include "ligne_commande.h"
#include <unistd.h>
#include <stdio.h>

/**
* Elle lit une commande et l’exécuter. La lecture de cette ligne se fait grâce à la fonction ligne_commande présente dans le fichier ligne_commande.h.
* Pour exécuter la commande, j'utilise la fonction execvp. 
* Il y est ajouté les traitements nécessaires pour prendre en compte les exécutions en tâche de fond (gestion du caractère «&» en fin de ligne).
**/
void execute_ligne_commande()
{
  int flag = 0;
  int nb = 0;
  int x = 0;
  char *** iutsh = ligne_commande(&flag,&nb);
  //iutsh[x][y][z] ou x est ici nb, y les arguments de x et z est y carcatere par caractere. A chaque fois fini par null.
  for(x=0; x<nb;x++) {
    execvp(iutsh[x][0],iutsh[x]);
  }
}

int main()//int argc,char * argv[])
{
  execute_ligne_commande();
  return 1;
}
