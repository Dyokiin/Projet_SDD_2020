/* users.c */

#include "users.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fichier.h"
#include "lettre.h"

#define clear() printf("\033[H\033[J")
#define LONGEUR 17

enum statut { BASIC, ADMIN, SUPERADMIN};

/* Structure utilisateur Identifiant (14 characteres max) + mot de passe (14 characteres max) */
struct s_user { //structure utilisateur (Identifiant + Mot de passe)
    char ID[LONGEUR] ;
    char password[LONGEUR];
    enum statut s;
};

/*affiche un utilisateur */
void afficher_user(User u){
    printf("Identifiant: \"%s\" Mot de passe: \"%s\" Statut \"%d\"\n",u->ID,u->password, u->s );
}


/*lecture corecte si taille strictement superieur a 3 et inferieur a longueur-2 (attention carateres autorises (reagrder fichier caracteres autorises))*/
int lire (char *chaine,int longueur) {
    char *pointeur=NULL;
    if (fgets(chaine,longueur-1,stdin) != NULL) {
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


int new_user(){
    User u=(User)malloc(sizeof(User));
    printf("Votre nom d'utilisateur doit etre de taille min 4 et max %d. Ne pas contenir : d'espace,tab,é,ç,à,etc.\nEntrez nom d'utilisateur :",LONGEUR-3);
    do {
        while(!lire(u->ID,LONGEUR)){
            printf("Entrez nom d'utilisateur :");
        }
    } while(recherche_occ(u->ID) && printf("Identifiant deja existant. Entrez un autre nom d'utilisateur :"));

    printf("Votre mot de passe doit etre de taille min 4 et max %d. Ne pas contenir : é,ç,à,etc.\nEntrez mot de passe :", LONGEUR-3);
    while(!lire(u->password,LONGEUR)){
        printf("Entrez mot de passe :");
    }
    u->s=BASIC;
    //afficher_user(u);
    save_user(u);
    return 1;
}

int save_user(User u){
    char password_chiffre[500];
    chiffrement(u->password,password_chiffre);
    if (!ecriture()) {
        printf("Ecriture impossible : pas acces fichier. Compte non enregistrer\n");
    }
    return 1;
}

int connexion(){
    char Identifiant[LONGEUR];
    do { //mettre un exit
        printf("Entrez nom d'utilisateur :");
        while(!lire(Identifiant,LONGEUR)){
            printf("Erreur : caracteres non autorises. Entrez nom d'utilisateur :");
        }
        //printf("%d\n",recherche_occ(u->ID) );
    } while(!recherche_occ(Identifiant) && printf("Identifiant inexistant. "));
    char Mdp[LONGEUR];
    char Mdp_chiffre[100];
    char ligne[100];
    do { //ajouter une sortie/retour
        printf("Entrez mot de passe :");
        while(!lire(Mdp,LONGEUR)){
            printf("Erreur : caracteres non autorises. Entrez mot de passe :");
        }
        chiffrement(Mdp,Mdp_chiffre);
        recherche(Identifiant,ligne);
        //printf("%s\n",Mdp_chiffre );
        //printf("%s\n",ligne );
        //printf("%s\n",strstr(ligne,Mdp_chiffre) );
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
    char chaine[4];
    while (!lire_menu_1ou2(chaine)) {
        printf("Erreur reessayer. ");
    }
    clear();
    if(chaine[0]=='1'){
        printf("Connexion\n" );
        connexion();
    }
    if(chaine[0]=='2'){
        printf("Creation d'un compte\n");
        new_user();
    }
    printf("ok.\n");
    return 1;
}


int main(int argc, char *argv[]) {
    menu_connexion();
    //new_user();
    //recherche_occ(a1->ID);

    /*char* a="12345";
    char* b="ARA 123";
    User u=user(a,b);
    printf("id : %s  mdp : %s \n",u->ID, u->password );
    afficher_user(u);
    printf("\n\n");
    char chaine[16]; // max 14 characteres
    while(!lire(chaine,16)){
        printf("Erreur recommencer\n");
    }
    printf("YES\n");
    printf("%s\n",chaine );*/
    /*int i=0;
    while (i<16 && i!=-1) {
        if (chaine1[i]=='\0'){
            printf("parfait\n");
            i=-1;
        }
        else{
            i++;
        }
    }
    if (i==16){
        printf("nul\n");
    }
    printf("%s\n",chaine1 );
*/
    return 0;
}
