all : easyshare

easyshare : main.o gestion_ressources.o gestion_utilisateurs.o
	gcc $(pkg-config --cflags --libs gtk+-2.0) -lm -o easyshare main.o gestion_ressources.o gestion_utilisateurs.o -I.

main.o : ./EasyShare.c ./gestion_utilisateurs.h ./gestion_ressources.h
	gcc -o ./main.o ./EasyShare.c 
gestion_ressource.o : ./gestion_ressources.c ./gestion_ressources.h
	gcc -o gestion_ressources.o gestion_ressources.c
gestion_utilisateurs.o : gestion_utilisateurs.c gestion_utilisateurs.h
	gcc -o gestion_utilisateurs.o gestion_utilisateurs.c
