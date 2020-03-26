/* toute la gestion des ustilisateurs : creation de compte,
connexion, modification mot de passe. donc premier menu */

#include "user.h"
#include "fichier.h"
#include "chiffrement.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define clear() printf("\033[H\033[J")
#define LONGEUR 16



enum statut { BASIC, ADMIN, SUPERADMIN};

struct s_user {
    char *id;
    char *password;
    enum statut s;
};


int new_user(){
    User u=(User)malloc(sizeof(struct s_user));
    u->id=(char *)malloc(sizeof(char)*LONGEUR);
    u->password=(char *)malloc(sizeof(char)*LONGEUR);
    if(u==NULL || u->id==NULL || u->password==NULL){
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    printf("Votre nom d'utilisateur doit etre de taille min 4 et max %d. Ne pas contenir : d'espace,tab,é,ç,à,etc. Saisissez 'q' pour retourner au menu\nEntrez nom d'utilisateur :",LONGEUR-2);
    do {
        while(!lire(u->id)){
            printf("Entrez nom d'utilisateur :");
        }
        if (*(u->id)=='q'){
            return -1;
        }
    } while(recherche_occ(u->id) && printf("Identifiant deja existant. Entrez un autre nom d'utilisateur :"));

    printf("Votre mot de passe doit etre de taille min 4 et max %d. Ne pas contenir : é,ç,à,etc. Saisissez 'q' pour retourner au menu\nEntrez mot de passe :", LONGEUR-2);
    while(!lire(u->password)){
        printf("Entrez mot de passe :");
    }
    if (*(u->password)=='q'){
        return -1;
    }
    u->s=BASIC;
    save_user(u);
    free(u->id);
    free(u->password);
    free(u);
    printf("Compte créé !!\n");
    return 1;
}


int lire (char *chaine) {
    char *pointeur=NULL;
    if (fgets(chaine,LONGEUR,stdin) != NULL) {
        if (strlen(chaine)==2 && chaine[0]=='q'){
            return 1;
        }
        if (strlen(chaine)<5){
            printf("Erreur : taille trop petite. ");
            return 0;
        }
        pointeur = strchr(chaine, '\n');
        if (pointeur != NULL) {
            *pointeur = '\0';
            for (int i=0; i<strlen(chaine); i++) {
                if (chaine[i]<33 || chaine[i]>126){
                    printf("Erreur : caracteres non autorises. ");
                    return 0;
                }
            }
            return 1;
        }
    }
    int b = 0;
    while (b != '\n' && b != EOF) {
        b = getchar();
    }
    printf("Erreur : taille trop grande. ");
    return 0;
}

int save_user(User u){
    char password_chiffre[200];
    chiffrement(u->password,password_chiffre);
    if (!ecriture(u->id,password_chiffre)) {
        printf("Ecriture impossible : pas acces fichier. Compte non enregistrer\n");
    }
    return 1;
}


int connexion(){
    char Identifiant[LONGEUR];
    do { //mettre un exit
        printf("Saisissez 'q' pour retourner au menu. Entrez nom d'utilisateur :");
        while(!lire(Identifiant)){
            printf("Entrez nom d'utilisateur :");
        }
        if(*Identifiant=='q'){
            return -1;
        }
    } while(!recherche_occ(Identifiant) && printf("Identifiant inexistant. "));
    char Mdp[LONGEUR];
    char Mdp_chiffre[100];
    char ligne[100];
    do { //ajouter une sortie/retour
        printf("Entrez mot de passe :");
        while(!lire(Mdp)){
            printf("Entrez mot de passe :");
        }
        if(*Mdp=='q'){
            return -1;
        }
        chiffrement(Mdp,Mdp_chiffre);
        recherche(Identifiant,ligne);
    } while(strstr(ligne,Mdp_chiffre)==NULL && printf("Mot de passe errone. "));
    printf("Connexion Réussi !!\n");
    return 1;
}

int lire_menu_1ou2 (char *chaine) {
    char *pointeur=NULL;
    printf("Entrez 1 ou 2 :");
    if (fgets(chaine,3, stdin) != NULL) {
        //printf("%s\n",chaine );
        pointeur = strchr(chaine, '\n');
        if (pointeur != NULL) {
            //printf("non nul\n");
            *pointeur = '\0';
            for (int i=0; i<strlen(chaine); i++) {
                //printf("%c\n",chaine[i] );
                if (chaine[i]>48 && chaine[i]<51){
                    //printf("YES\n");
                    return 1;

                }
            }
            return 0;
        }
    }
    int b = 0;
    while (b != '\n' && b != EOF) {
        b = getchar();
    }
    return 0;
}


int menu_connexion(){
    printf("1. Connexion\n2. Creation d'un compte\n");
    char chaine[3];
    while (!lire_menu_1ou2(chaine)) {
        printf("Erreur reessayer. ");
    }
    clear();
    if(chaine[0]=='1'){
        printf("Connexion Saisissez 'q' pour retourner au menu. \n" );
        int a=connexion();
        if (a==-1){
            menu_connexion();
        }

    }
    if(chaine[0]=='2'){
        printf("Creation d'un compte\n");
        int b=new_user();
        if (b==-1){
            menu_connexion();
        }
    }
    return 1;
}
