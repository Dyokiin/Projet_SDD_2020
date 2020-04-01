#include "gestion_utilisateur.h"
#include "interaction_fichier.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LONGEUR 10

enum statut { BASIC, ADMIN, SUPERADMIN};

struct s_user {
    char *login;
    char *password;
    enum statut s;
    char *nom=NULL;
    char *prenom=NULL;
    char *email=NULL;
};

/* creer un nouvelle utilisateur avec login password demande puis statut BASIC, et nom/prenom/email a renseigner plus tard*/
int new_user(){
    User u=(User)malloc(sizeof(struct s_user));
    u->login=(char *)malloc(sizeof(char)*LONGEUR);
    u->password=(char *)malloc(sizeof(char)*LONGEUR);
    if(u==NULL || u->login==NULL || u->password==NULL){
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    printf("Votre nom d'utilisateur doit etre de taille min 4 et max %d. Ne pas contenir : d'espace,tab,\",é,ç,à,etc.\n",LONGEUR-2);
    int retour=0;
    while(!retour){
        printf("Entrez un login :");
        retour=lire_long_moy(u->login);
        if (retour==1 && recherche_occurence_login(u->login)==1){
            printf("Identifiant deja existant.");
            retour=0;
        }
        if(retour==-1){
            return -1;
        }
    }

    printf("Votre mot de passe doit etre de taille min 4 et max %d. Ne pas contenir : é,ç,à,etc.\n", LONGEUR-2);
    retour=0;
    while(!retour){
        printf("Entrez un mot de passe :");
        retour=lire_long_moy(u->password);
        if(retour==-1){
            return -1;
        }
    }
    u->s=BASIC;
    retour=0;
    if (ajout_ligne_utilisateur(u->login,u->password,u->s,u->nom, u->prenom, u->email) && creation_fichier_historique_utilisateur(u->login)){
        retour=1
    }
    free(u->id);
    free(u->password);
    free(u);
    return retour;
}




change_password)()
change_statut()
change_nom()
change_prenom()
change_email()

Connexion()

chiffrement()
