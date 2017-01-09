/**
* Controle TP du 09 janvier 2017
* 
* Nom    : PROCHNOW
* Prenom : FREDERIC
* Groupe : N
**/


#define FILENAME_SIZE 256
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> 

typedef struct {
  char fichier[FILENAME_SIZE];
} job_t;



/*
Ici je stocke dans un buffer une structure stat correspondant aux informations contenant dans "fichier".
Pour cela je crée un struct stat *buf pour ensuite l'utiliser.
Ensuite j'affiche certaines valeurs contenus dans le buffer.
J'utilise -> parcequ'il s'agit d'un pointeur et non un '.'.
*/
int afficher_details(const char *fichier)
{
  struct stat *buf = 0;
  stat(fichier,buf);
  //printf(%s','%s','%d,buf->st_mode,buf->st_dev,buf->st_size);
  return 0;
}

/*
Dans cette methode j'écris la valeur contenus dans la structure job dans l'entier fd(file descripteur).
J utilise dans cette mùethode sizeof(int) car c'est bien dans fd qui est un int que l 'on va ecrire.
Si l'écriture a fonctionner, la fonction retourne 0.
En cas de probleme, la methode retourne -1 avec un message d erreur.
*/
int envoyer_job(int fd, const job_t *job)
{
  if(write(fd, &(job->fichier),sizeof(int))) {
  	return 0;
  } else {
        perror("envoyer_job: write:");
        return -1;
  }
  
}

/*
Comme dans envoyer_job, il s'agit du contraire avec cette methode.
Je vais lire dans le file descripteur 'fd' sa valeur pour la stocker dans la structure job.a
J utilise ici sizeof(char) car on stocke la valeur du file descripteur "fd" dans un char contennat dans la structure.
Comme dans la methode precedente, si la lecture a fonctionner, la fonction retourne 0.
En cas de probleme, la methode retourne -1 avec un message d erreur.
*/
int recevoir_job(int fd,job_t *job)
{
  if(read(fd, &(job->fichier),sizeof(char))) {
    return 0;
  } else {
    perror("recevoir_job: read :");
    return -1;
  }
}

/*
Maintenant on s'interese aux procesus.
Le programme doit continuer tant qu'il y a du travail dans le decripteur fd : pour cela, la methode recevoir_job retourne -1 en cas de probleme.
Dans notre cas, le probleme peut-etre que le descripteur a ete vider. On le sait grace au retour de la fonction,
tant qu'elle retourne 0 c'est ok apres c'est un stop. On arrete.
Dans cette boucle, j'utilise la premiere methode pour afficher le details du fichier contenus dans la structure job.
Ensuite, j'affiche un message de fin puis quitte le processus avec exit(0);
*/
void traitement_fils(int fd)
{
  job_t *job = 0;
  while(recevoir_job(fd,job)!=-1) {
    afficher_details(job->fichier);
  }
  printf("--Je vous indique la terminaison de cette methode");
  exit(0);   
}

/*
La methode doit creer un fils et effectuer un traitement (methode precedente).
Je stocke le pid ou numero de procesus generer par l'appel de fork(). fork() servant a ceer un processus fils.
Tant que ce pid est egal a 0, ce qui signifie qu'il est dans le fils et que le traitement n est pas fini.
je ferme l'entree (0) du tube pour effectuer le traitement sur  la sortie du tube (1). Je retourne suite le numero de procesus
ou pid du fils.
En cas d'erreur on retourne -1 avec message d'erreur.
*/
int creer_fils(int tube[2])
{
  int pid = fork();
  if(pid == 0){
    close(tube[0]);
    traitement_fils(tube[1]);
    return pid;
  }else {
    perror("creer_fils: ");
    return -1;
  }    
}

/*
Maintenant on s'occupe du main.
Je verifis le nombre d arguments passes en parametres grace a argc puis pour chaque fils crer je recupere son numero de procesus et
met un message signalant la fin du procesus.
*/
int main(int argc,char ** argv)
{
  int i;
  int tube[2];
  if(argc>=2){
    for(i=0; i<(int)argv[0][0];i++){
      int pid = creer_fils(tube);
      printf("Procesus %d : FINI",pid);
    }
    return 0;
  }
  return -1;
}
