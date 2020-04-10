all : easyshare

easyshare : main.o gestion_ressource.o gestion_utilisateurs.o
	cc -o easyshare main.o gestion_ressource.o gestion_utilisateurs.o 

main.o : main.c gestion_utilisateurs.h gestion_ressource.h
	cc $(pkg-config --cflags --libs gtk+-2.0) -lm -o main.c
gestion_ressource.o : gestion_ressource.c gestion_ressource.h
	cc -o gestion_ressource.c
gestion_utilisateurs.o : gestion_utilisateurs.c gestion_utilisateurs.h
	cc -o gestion_utilisateurs.c
