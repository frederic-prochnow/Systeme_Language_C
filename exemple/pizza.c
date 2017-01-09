/* Contrôle TP ASR4 : 25 mars 2014 */

/* Nom    :
 * Prénom :
 * Groupe :
 */

/* Votre fichier doit compiler sans erreur avec les options de compilation :
 *  -Wall -Werror -pedantic
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "pizza.h"


/* IMPLEMENTATION DES FONCTIONS A FAIRE ICI */

/* Stoppe un producteur */
/* Cette fonction NE DOIT PAS être modifiée */
void stop_producer(int pid)
{
    kill(pid, SIGKILL);
}

int pizza_ready(struct stock *s)
{
	if(s->bread>=1){
		if(s->tomato>=3){
			if(s->cheese>=2){
				if(s->ham>=2){
					return 0;
				}
			}
		}
	}
	return -1;
}

int create_consumer(int fd[2])
{
	int pid = fork();
	if(pid == 0){
		struct stock s;
		while(pizza_ready(&s) == -1){
			close(fd[0]);
			char buf[sizeof(int)];
			int ingredient = read(fd[1], &buf, sizeof(int));
			if(ingredient == 0){
				s.bread += 1;
			}else if(ingredient == 1){
				s.tomato += 1;
			}else if(ingredient == 2){
				s.cheese += 1;
			}else if(ingredient == 3){
				s.ham += 1;
			}
			sleep(1);
		}
		printf("Kowabunga\n");
		stop_producer(pid);
		exit(0);
	}else{
		return -1;
	}

}

int create_producer(int fd[2], int ingredient, int delay)
{
	int pid = fork();
	if(pid > 0){
		while(1){
			close(fd[1]);
			write(fd[0], (void *) &ingredient, sizeof(int));
			sleep(delay);
		}
		exit(pid);
	}else{
		return -1;
	}
}

int init_producers(int fd[2], int pid_producers[4])
{
	
}

int main(void/*int argc, char *argv[]*/)
{
    /* Votre code ici */
    return 0;
}