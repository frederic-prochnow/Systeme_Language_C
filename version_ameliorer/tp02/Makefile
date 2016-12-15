# Les options de compilation
CFLAGS = -Wall -W -Werror
# Le compilateur utilisé. On peut par exemple le changer par clang
CC = gcc

# La première règle du makefile est exécutée par défaut
# La cible est le nom de l'exécutable, les dépendances
# sont les fichiers .o
# L'action correspond à l'édition de lien.
# $@ est le nom de la cible
# $^ est la liste des dépendances
tp02: main.o entiers.o
	$(CC) -o $@ $^

# Les dépendances des fichiers .o
# On ne précise pas d'action dans ces règle car make fournit
# des règles implicites pour la compilation de code C.
# En d'autre terme, il "sait" comment compiler.
# Attention, les options de compilation utilisées sont données par
# la variable CFLAGS. Ce nom n'est donc pas choisi au hasard!

# Ici, le fichier main.c inclu le fichier entiers.h, on l'ajoute donc
# aux dépendances
main.o: main.c entiers.h
entiers.o: entiers.c


# Les règles de nettoyage:
# clean supprime les fichiers .o
# mrproper rappelle clean et supprime en plus l'exécutable
# le .PHONY sert à indiquer que ces règles ne sont jamais à jour
# et doivent être exécutée à chaque fois que c'est demandé
.PHONY: clean mrproper
clean:
	$(RM) main.o entiers.o
mrproper: clean
	$(RM) $(OUTPUT)
