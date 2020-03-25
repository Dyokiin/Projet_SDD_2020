/* users.c */

#include "users.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fichier.h"

#define LONGEUR 16

enum statut { BASIC, ADMIN, SUPERADMIN};

/* Structure utilisateur Identifiant (15 characteres max) + mot de passe (15 characteres max)
puis verifier si Identifiant d�k� existant*/
struct s_user { //structure utilisateur (Identifiant + Mot de passe)
    char ID[16] ;
    char password[16];
    enum statut s;
};




void afficher_user(User u){
    printf("Identifiant: \"%s\" Mot de passe: \"%s\" Statut \"%d\"\n",u->ID,u->password, u->s );
}


/*lecture corecte si taille strictement superieur a 3 et inferieur a longueur-2 (attention carateres autorises)*/
int lire (char *chaine,int longueur) {

    char *pointeur=NULL;
    if (fgets(chaine, longueur, stdin) != NULL) {
        if (strlen(chaine)<5){
            return 0;
        }
        pointeur = strchr(chaine, '\n');
        if (pointeur != NULL) {
            *pointeur = '\0';
            for (int i=0; i<strlen(chaine); i++) {
                //printf("%c\n",chaine[i] );
                if (chaine[i]<33 || chaine[i]>126){
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
    return 0;
}


User new_user(){
    User u=(User)malloc(sizeof(User));
    printf("Entrez un nom d'utilisateur de taille %d \n",LONGEUR-2);
    while((!lire(u->ID,LONGEUR)) && recherche_occ(u->ID)){
        printf("Erreur recommencer\n");
    }
    printf("Entrez un mot de passe taille %d\n", LONGEUR-2);
    while(!lire(u->password,LONGEUR)){
        printf("Erreur recommencer\n");
    }
    u->s=BASIC;
    return u;
}

int save_user(){
    return 1;
}


int main(int argc, char *argv[]) {
    User a1;
    a1=new_user();
    afficher_user(a1);

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
