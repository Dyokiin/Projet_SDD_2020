all : easyshare

easyshare : main.o gestion_ressource.o gestion_utilisateurs.o
	gcc $(pkg-config --cflags --libs gtk+-2.0) -lm -o easyshare main.o gestion_ressource.o gestion_utilisateurs.o -I.

main.o : main.c gestion_utilisateurs.h gestion_ressource.h
	gcc -o main.c
gestion_ressource.o : gestion_ressource.c gestion_ressource.h
	gcc -o gestion_ressource.c
gestion_utilisateurs.o : gestion_utilisateurs.c gestion_utilisateurs.h
	gcc -o gestion_utilisateurs.c
