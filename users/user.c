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
    printf("Votre nom d'utilisateur doit etre de taille min 4 et max %d. Ne pas contenir : d'espace,tab,é,ç,à,etc.\nEntrez nom d'utilisateur :",LONGEUR-2);
    do {
        while(!lire(u->id)){
            printf("Entrez nom d'utilisateur :");
        }
        if (*(u->id)=='q' && strlen(u->id)==2){
            return -1;
        }
    } while(recherche_occ(u->id) && printf("Identifiant deja existant. Entrez un autre nom d'utilisateur :"));

    printf("Votre mot de passe doit etre de taille min 4 et max %d. Ne pas contenir : é,ç,à,etc.\nEntrez mot de passe :", LONGEUR-2);
    while(!lire(u->password)){
        printf("Entrez mot de passe :");
    }
    if (*(u->password)=='q' && strlen(u->password)==2){
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
    if (!ecriture(u->id,password_chiffre,u->s)) {
        printf("Ecriture impossible : pas acces fichier. Compte non enregistrer\n");
    }
    return 1;
}


int connexion(User u){
    do { //mettre un exit
        printf("Entrez nom d'utilisateur :");
        while(!lire(u->id)){
            printf("Entrez nom d'utilisateur :");
        }
        if(*(u->id)=='q' && strlen(u->id)==2){
            return -1;
        }
    } while(!recherche_occ(u->id) && printf("Identifiant inexistant. "));
    char Mdp[LONGEUR];
    char Mdp_chiffre[100];
    char ligne[100];
    do { //ajouter une sortie/retour
        printf("Entrez mot de passe :");
        while(!lire(Mdp)){
            printf("Entrez mot de passe :");
        }
        if(*Mdp=='q' && strlen(Mdp)==2){
            return -1;
        }
        chiffrement(Mdp,Mdp_chiffre);
        recherche(u->id,ligne);
    } while(strstr(ligne,Mdp_chiffre)==NULL && printf("Mot de passe errone. "));
    //printf("%s\n",ligne );
    //printf("%c %c\n",ligne[1],ligne[2] );
    (u->s)=ligne[0]-'0';
    printf("Connexion Réussi !!\n");
    return 1;
}

int lire_menu_1ou2ou3 (char *chaine) {
    char *pointeur=NULL;
    printf("Entrez 1 ou 2 ou 3 :");
    if (fgets(chaine,3, stdin) != NULL) {
        //printf("%s\n",chaine );
        pointeur = strchr(chaine, '\n');
        if (pointeur != NULL) {
            //printf("non nul\n");
            *pointeur = '\0';
            for (int i=0; i<strlen(chaine); i++) {
                //printf("%c\n",chaine[i] );
                if (chaine[i]>48 && chaine[i]<52){
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
    clear();
    printf("BIENVENUE\n");
    printf("1. Connexion\n2. Creation d'un compte\n3. Quiter\n");
    char chaine[3];
    while (!lire_menu_1ou2ou3(chaine)) {
        printf("Erreur reessayer. ");
    }
    if(chaine[0]=='1'){
        printf("Connexion. Saisissez 'q' pour retourner au menu. \n" );
        User u_actuel=(User)malloc(sizeof(struct s_user));
        u_actuel->id=(char *)malloc(sizeof(char)*LONGEUR);
        int a=connexion(u_actuel);
        if (a==-1){
            free(u_actuel->id);
            free(u_actuel);
            menu_connexion();
        }
        if (a==1){
            clear();

            if(u_actuel->s==0){
                menu_utilisateur(u_actuel);
            }
            else if(u_actuel->s==1){
                menu_admin(u_actuel);
            }
        }

    }
    if(chaine[0]=='2'){
        printf("Creation d'un compte. Saisissez 'q' pour retourner au menu.\n");
        new_user();
        menu_connexion();
    }
    return 1;
}
int menu_utilisateur(User u){
    printf("Bienvenue %s \n",u->id);
    printf("1. Modifer mdp\n2. enregistrer une ressource\n3. emprunter une ressource\n4. supprimer une ressource\n5. voir historique\n");
    char choix[3];
    while (!lire_menu_1ou2ou3(choix)) {
        printf("Erreur reessayer. ");
    }
    if(choix[0]=='1'){
        if(printf("Saisissez 'q' pour retourner au menu. ") && !modifier_password(u->id)){
            clear();
            menu_utilisateur(u);
        }
        else{
            printf("Reconnectez vous\n");
            free(u->id);
            free(u);
            menu_connexion();
        }
    }
    else{
        free(u->id);
        free(u);
    }
    return 1;
}
int menu_admin(User u){
    printf("Bienvenue %s \n",u->id);
    printf("Menu ADMIN\n1. Modifer mdp\n2.Modifier mdp n'importe quel user\n3. enregistrer une ressource\n3. emprunter une ressource\n4. supprimer une ressource\n5. voir historique\n");
    char choix[3];
    while (!lire_menu_1ou2ou3(choix)) {
        printf("Erreur reessayer. ");
    }
    if(choix[0]=='1'){
        if(printf("Saisissez 'q' pour retourner au menu. ") && !modifier_password(u->id)){
            clear();
            menu_admin(u);
        }
        else{
            printf("Reconnectez vous\n");
            free(u->id);
            free(u);
            menu_connexion();
        }
    }
    else{
        if(choix[0]=='2'){
            if(!admin_modifier_password()){
                clear();
                menu_admin(u);
            }
            else{
                clear();
                menu_admin(u);
            }
        }
        free(u->id);
        free(u);
    }
    return 1;
}


int modifier_password(char *login){
    char new_password[LONGEUR];
    printf("Votre mot de passe doit etre de taille min 4 et max %d. Ne pas contenir : é,ç,à,etc.\nEntrez mot de passe :", LONGEUR-2);
    while(!lire(new_password)){
        printf("Entrez mot de passe :");
    }
    if (*(new_password)=='q'&& strlen(new_password)==2){
        return 0;
    }
    char new_password_chiffre[100];
    chiffrement(new_password,new_password_chiffre);
    modifier_ligne(login,new_password_chiffre);
    return 1;

}

int admin_modifier_password(){
    char login[LONGEUR];
    printf("Saisissez 'q' pour retourner au menu. ");
    do { //mettre un exit
        printf("Entrez nom d'utilisateur :");
        while(!lire(login)){
            printf("Entrez nom d'utilisateur :");
        }
        if(*(login)=='q' && strlen(login)==2){
            return 0;
        }
    } while(!recherche_occ(login) && printf("Identifiant inexistant. "));
    if(!modifier_password(login)){
        return 0;
    }
    return 1;
}
