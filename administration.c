/* Gestion de la création, emprunt et retour des objets par et entre les utilisateurs */

#include "administration.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getters.h"

//#include "user.h"
 

#define clear() printf("\033[H\033[j")
#define MAX 24


enum type { OUTILS, SERVICES, LIVRES, VEHICULES };

struct s_objet {
	//User u;
	char *name;
	int *prtr;
	enum type t;
} ;


int type_choice(){ /* Permet de choisir le type d objet desire */
	int n = 1;
	int choice = 0;
	while (n=1) {
		printf("Que pretez vous ?\nOutil ? 	Tapez 1\nService ?	Tapez 2\nLivre ?	Tapez 3\nVehicule ?	Tapez 4\n [1/2/3/4]");
		int i = getints();
		switch(i) {
			case 1 :
				choice = 1;
				break;
			case 2 :
				choice = 2;
				break;
			case 3 :
				choice = 3;
				break;
			case 4 :
				choice = 4;
				break;
			default :
				break;
		}
		if (choice =! 0) {
			n = 0;
		} else {
			printf("Erreur : veuillez indiquer le chiffre 1 ou 2 ou 3 ou 4.");
		}
	}
	clear() ;
	return choice ;
}



int save_object(Objet o){
	
	return 0;
}




int create_object() {
	Objet o =(Objet)malloc(sizeof(struct s_objet));
	//o->u =(User)malloc(sizeof(struct User));
	o->name =(char *)malloc(sizeof(char)*MAX);
	o->prtr =malloc(sizeof(int));
	if(o==NULL || /*o->u==NULL ||*/ o->name==NULL || o->prtr==NULL){
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	printf("Nom de ce que vous pretez (max 20 caracteres): ");
	o->name = getchars();
	//o->u = u_actuel ;
	o->prtr = 0;
	int i = type_choice();
	switch (i) {
		case 1:
			o->t = OUTILS;
			break;
		case 2:
			o->t = SERVICES;
			break;
		case 3:
			o->t = LIVRES;
			break;
		case 4:
			o->t = VEHICULES;
			break;
	}
	save_object(o);
	free(o->name);
	//free(o->u);
	free(o->prtr);
	printf("Objet créé.");
	return 0;
}
	
