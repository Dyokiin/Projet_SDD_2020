#include "gestion_utilisateurs.h"
#include "gestion_ressources.h"
#include "gestion_graphique.h"
#include "lecture.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define clear() printf("\033[H\033[J")
#define LONGEUR 22

enum statut { BASIC, ADMIN, SUPERADMIN};

struct s_user {
    char *login;
    char *password;
    enum statut s;
    char *nom;
    char *prenom;
    char *email;
};

int menu_utilisateur(User u){
    printf("    MENU utilisateur\n(1) Recherche\n(2) Gestion des ressources\n(3) Administration\n(4) Quitter\n");
    char chaine[3];
    while(!lire_menu_1ou2ou3ou4(chaine)){
        printf("Erreur, reessayer ");
    }
    if (chaine[0]=='1'){
        clear();
        menu_recherche(u);
    }
    else if (chaine[0]=='2'){
        clear();
        menu_gestion_ressource(u);
    }
    else if (chaine[0]=='3'){
        clear();
        menu_gestion_administration(u);
    }
    return 1;
}

int menu_recherche(User u){
    printf("    RECHERCHE\n");
    int type;
    recherche_par_type(u->login,&type);
    printf("(1) Emprunter une ressource\n(2) Retour recherche\n(3) Retour menu\n");
    char chaine[3];
    while(!lire_menu_1ou2ou3(chaine)){
        printf("reessayer ");
    }
    if (chaine[0]=='1'){
        int compteur;
        afficher_ressource_type_nb(type,u->login,&compteur);
        int nb_retour=0;
        printf("(%d) Retour au menu principal\n",compteur+1);
        while(nb_retour<1 || nb_retour>compteur+1){
            while (!lire_nb_ressource(&nb_retour)) {
                printf("reessayer ");
            }
        }
        if(nb_retour!=compteur+1){
            emprunter_ressource_type(type,u->login,nb_retour);
            printf("Emprunt effectué\n" );
        }
        menu_utilisateur(u);
    }
    else if (chaine[0]=='2'){
        menu_recherche(u);
    }
    else {
        menu_utilisateur(u);
    }
    return 1;
}


int menu_gestion_administration(User u){
    printf("    ADMINISTRATION\n\n(1) Changer password\n(2) Changer nom\n(3) Changer prenom\n(4) Changer email\n(5) Retour menu principal\n");
    char chaine[3];
    while(!lire_menu_1ou2ou3ou4ou5(chaine)){
        printf("Erreur, réessayer ");
    }
    if(chaine[0]=='1'){
        clear();
        printf("mdp\n");
        change_password(u);
        clear();
        menu_gestion_administration(u);
    }
    else if(chaine[0]=='2'){
        clear();
        printf("nom\n");
        change_nom(u);
        clear();
        menu_gestion_administration(u);
    }
    else if(chaine[0]=='3'){
        clear();
        printf("prenom\n");
        change_prenom(u);
        clear();
        menu_gestion_administration(u);
    }
    else if(chaine[0]=='4'){
        clear();
        printf("email\n");
        change_email(u);
        clear();
        menu_gestion_administration(u);
    }
    else{
        clear();
        printf("retour\n");
        menu_utilisateur(u);
    }
    return 1;
}



int menu_admin(User u){
    printf("MENU ADMIN\n");
    return 1;
}

int menu_gestion_ressource(User u){
    printf("    GESTION DES RESSOURCES\n\n(1) Gestion ressources empruntées\n(2) Gestion ressources pretees\n(3) Creer une nouvelle ressource\n(4) Retour au menu principal\n");
    char chaine[3];
    while (!lire_menu_1ou2ou3ou4(chaine)) {
        printf("Erreur, reessayer. ");
    }
    if(chaine[0]=='1'){
        clear();
        printf("ressouces empruntées\n" );
        afficher_ressources_empruntees(u->login);
        printf("\n(1) Rendre une ressouces\n(2) Vide \n(3) Retour\n" );
        char chaine[3];
        while (!lire_menu_1ou2ou3(chaine)) {
            printf("Erreur. reessayer ");
        }
        if (chaine[0]=='1'){
            clear();
            printf("    Rendre ressource\n");
            int compteur;
            afficher_ressources_empruntees_compteur(u->login,&compteur);
            printf("(%d) Retour au menu\n",compteur+1 );
            int nb_retour=0;
            while (nb_retour<1 || nb_retour>compteur+1) {
                while(!lire_nb_ressource(&nb_retour)){
                    printf("reessayer. ");
                }
            }
            if(nb_retour!=compteur+1){
                rendre_ressource(u->login,nb_retour);
            }
            printf("%d\n",nb_retour );
            menu_gestion_ressource(u);

        }
        else if(chaine[0]=='2'){
            menu_gestion_ressource(u);

        }
        else{
            clear();
            menu_gestion_ressource(u);
        }


    }
    else if(chaine[0]=='2'){
        clear();
        printf("ressources pretées\n");
        afficher_ressources_pretees(u->login);
        menu_gestion_ressource(u);

    }
    else if(chaine[0]=='3'){
        clear();
        printf("new ressource\n");
        nouvelle_ressource(u->login);
        menu_gestion_ressource(u);
    }
    else {
        clear();
        printf("Retour\n");
        menu_utilisateur(u);
    }
    return 1;
}


/*1er menu declaration de la structure user et utilisation de la fonction connextion puis renvoie sur les different menu admin ou non*/

int menu_connexion_creation_compte(int i){
//    clear();
//    printf("    BIENVENUE\n");
//    printf("(1) Connexion\n(2) Creation d'un compte\n(3) Quiter\n");
//    char chaine[3];
//    while (!lire_menu_1ou2ou3(chaine)) {
//        printf("Erreur reessayer. ");
//    }
    if(i==1){
        User u_actuel=(User )malloc(sizeof(struct s_user));
        u_actuel->login=(char *)malloc(sizeof(char)*LONGEUR);
        u_actuel->password=(char *)malloc(sizeof(char)*100);
        u_actuel->nom=(char *)malloc(sizeof(char)*LONGEUR);
        u_actuel->prenom=(char *)malloc(sizeof(char)*LONGEUR);
        u_actuel->email=(char *)malloc(sizeof(char)*LONGEUR);
        int a=connexion(u_actuel);
        if (a==-1){
            free(u_actuel->email);
            free(u_actuel->nom);
            free(u_actuel->prenom);
            free(u_actuel->password);
            free(u_actuel->login);
            free(u_actuel);
        }
        else if (a==1){
            clear();
            printf("BONJOUR: ");
            afficher_user(u_actuel);
            if(u_actuel->s==0){
                menu_utilisateur(u_actuel);
            }
            else if(u_actuel->s==1){
                menu_admin(u_actuel);
            }
            free(u_actuel->email);
            free(u_actuel->nom);
            free(u_actuel->prenom);
            free(u_actuel->password);
            free(u_actuel->login);
            free(u_actuel);
            printf("Quitter avec succes\n");
        }

    }
    else if(i==2){
        clear();
        new_user();
    }
    //clear();

    return 1;
}

/*Affichier toute les sous elements de la struct user dans un printf fontion de test*/
void afficher_user(User u){
    printf("%s %s %d %s %s %s\n",u->login,u->password,u->s,u->nom,u->prenom,u->email );
}


/* creer un nouvelle utilisateur avec login password demande puis statut BASIC, et nom/prenom/email a renseigner plus tard*/
int new_user(){
    User u=(User)malloc(sizeof(struct s_user));
    u->login=(char *)malloc(sizeof(char)*LONGEUR);
    u->password=(char *)malloc(sizeof(char)*150);
    u->nom=(char *)malloc(sizeof(char)*3);
    u->prenom=(char *)malloc(sizeof(char)*3);
    u->email=(char *)malloc(sizeof(char)*3);
    char password_non_chiffre[LONGEUR];
    if(u==NULL || u->login==NULL || u->password==NULL || u->nom==NULL || u->prenom==NULL || u->email==NULL){
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    printf("Votre nom d'utilisateur doit etre de taille min 4 et max %d. Ne pas contenir : d'espace,tab,\",é,ç,à,etc.\n",LONGEUR-2);
    int retour=0;
    while(!retour){
        retour=lire_long_moy(u->login, "login");
        if (retour==1 && recherche_occurence_login(u->login)==1){
            printf("Identifiant deja existant.");
            retour=0;
        }
        if(retour==-1){
            free(u->login);
            free(u->password);
            free(u->prenom);
            free(u->nom);
            free(u->email);
            free(u);
            return -1;
        }
    }

    printf("Saisir 'q' pour revenir au menu. Votre mot de passe doit etre de taille min 4 et max %d. Ne pas contenir : é,ç,à,etc.\n", LONGEUR-2);
    retour=0;
    while(!retour){
        retour=lire_long_moy(password_non_chiffre, "Entrez un mot de passe");
        if(retour==-1){
            free(u->login);
            free(u->password);
            free(u->prenom);
            free(u->nom);
            free(u->email);
            free(u);
            return -1;
        }
    }
    chiffrement(password_non_chiffre,u->password);
    u->s=BASIC;
    strcpy(u->nom,"");
    strcpy(u->prenom,"");
    strcpy(u->email,"");
    retour=0;
    if (ajout_ligne_utilisateur(u) && creation_fichier_historique_utilisateur(u->login)){
        retour=1;
    }
    free(u->login);
    free(u->password);
    free(u->prenom);
    free(u->nom);
    free(u->email);
    free(u);
    return retour;
}


/*permet la connexion et le remplissage de la structure User et un retour si 'q' (return -1)*/
int connexion(User u){
    int retour=0;
    while(!retour){
	printf("vrai");
        retour=lire_long_moy(u->login, "Nom");
        if (retour==1 && recherche_occurence_login(u->login)==0){
            printf("Identifiant non existant.");
            retour=0;
        }
        if(retour==-1){
            return -1;
        }
    }
    retour=0;
    transforme_ligne_user_en_sa_structure(u);
    char mdp[30];
    char mdp_chiffre[100];
    while(!retour){
        retour=lire_long_moy(mdp, "Mot de passe");
        if (retour==1){
            chiffrement(mdp,mdp_chiffre);
            if(strcmp(mdp_chiffre,u->password)==0){
                retour=1;
            }
            else{
                printf("Mot de passe errone.");
                retour=0;
            }
        }
        if(retour==-1){
            return -1;
        }
    }
    return 1;
}


int change_password(User u){
    printf("Saisir 'q' pour revenir au menu. Votre mot de passe doit etre de taille min 4 et max %d. Ne pas contenir : é,ç,à,etc.\n", LONGEUR-2);
    int retour=0;
    char new_password[30];
    while(!retour){
        retour=lire_long_moy(new_password, "Nouveau mot de passe");
        if(retour==-1){
            return -1;
        }
    }
    chiffrement(new_password,u->password);
    supprimer_et_ajouter_ligne_utilisateur(u);
    return 1;

}
int change_statut(User u){
    printf("Saisir '3' pour revenir au menu. Votre statut doit etre de taille min 4 et max %d. Ne pas contenir : é,ç,à,etc.\n", LONGEUR-2);
    char chaine[3];
    printf("Entrez statut 1/2/3: ");
    while(!lire_menu_1ou2ou3 (chaine)){
        printf("Entrez statut 1/2/3: ");
    }
    if (chaine[0]=='3'){
        return -1;
    }
    u->s=chaine[0]-'0';
    supprimer_et_ajouter_ligne_utilisateur(u);
    return 1;
}
int change_nom(User u){
    printf("Saisir 'q' pour revenir au menu. Votre nom de famille doit etre de taille min 4 et max %d. Ne pas contenir : é,ç,à,etc.\n", LONGEUR-2);
    int retour=0;
    char new_nom[30];
    while(!retour){
        retour=lire_long_moy(new_nom, "Nom de famille");
        if(retour==-1){
            return -1;
        }
    }
    strcpy(u->nom,new_nom);
    supprimer_et_ajouter_ligne_utilisateur(u);
    return 1;


}
int change_prenom(User u){
    printf("Saisir 'q' pour revenir au menu. Votre prenom doit etre de taille min 4 et max %d. Ne pas contenir : é,ç,à,etc.\n", LONGEUR-2);
    int retour=0;
    char new_prenom[30];
    while(!retour){
        retour=lire_long_moy(new_prenom, "Prenom");
        if(retour==-1){
            return -1;
        }
    }
    strcpy(u->prenom,new_prenom);
    supprimer_et_ajouter_ligne_utilisateur(u);
    return 1;
}
int change_email(User u){
    printf("Saisir 'q' pour revenir au menu. Votre email doit etre de taille min 4 et max %d. Ne pas contenir : é,ç,à,etc.\n", LONGEUR-2);
    int retour=0;
    char new_email[30];
    while(!retour){
        retour=lire_long_moy(new_email, "Email");
        if(retour==-1){
            return -1;
        }
    }
    strcpy(u->email,new_email);
    supprimer_et_ajouter_ligne_utilisateur(u);
    return 1;
}


/*interprete la ligne du fichier pour la transformer dans la structure user pour pouvoir manipuler les informations*/
int transforme_ligne_user_en_sa_structure(User u){
    char ligne[300];
    recherche_login_renvoie_ligne(u->login,ligne);

    struct json_object *parsed_json;
    struct json_object *password;
    struct json_object *statut;
    struct json_object *nom;
    struct json_object *prenom;
    struct json_object *email;


    parsed_json = json_tokener_parse(ligne);

    json_object_object_get_ex(parsed_json, "password", &password);
    json_object_object_get_ex(parsed_json, "statut", &statut);
    json_object_object_get_ex(parsed_json, "nom", &nom);
    json_object_object_get_ex(parsed_json, "prenom", &prenom);
    json_object_object_get_ex(parsed_json, "email", &email);


    strcpy(u->password,json_object_get_string(password));
    u->s=json_object_get_int(statut);
    strcpy(u->nom,json_object_get_string(nom));
    strcpy(u->prenom,json_object_get_string(prenom));
    strcpy(u->email,json_object_get_string(email));
    return 1;
}


/*chiffre le mot de passe et le renvoie sur le pointeur password_chiffre */
int chiffrement(char *mdp,char* password_chiffre){
    char motconverti[100]="";

    for (int i=0; i<strlen(mdp); i++) {
        char b[2];
        sprintf(b,"%d",mdp[i]);
        strcat(motconverti,b);

    }

    //0 à ajouter pour former des blocs de 4
    int rajout_bloc=strlen(motconverti)%4;
    while(rajout_bloc<4 && rajout_bloc!=0){
        char a[100];
        strcpy(a,motconverti);
        motconverti[0]='0';
        motconverti[1]='\0';
        strcat(motconverti,a);
        rajout_bloc++;
    }
    //printf("%s\n",motconverti );

    /////////////////////////////////////////////////

    char bloc[5]="";
    password_chiffre[0]='\0';

    for (int compteur=0; 4*compteur<strlen(motconverti);compteur++){
        /*creer les blocs de 4 characteres*/
        for (int i=0; i<4;i++){
            bloc[i]=motconverti[4*compteur+i];
        }
        /*transforme char* en entier*/
        int bloc_int=atoi(bloc);

        //cryptage RSA par bloc de 4
        int n=3565343;
        int e = 7;
        long unsigned int bloc_c = bloc_int;
        for(int i=1; i<e;i++){
            bloc_c=(bloc_c*bloc_int)%n;
        }

        char bloc_chiffre_en_char[30];
        /* remet en chaine de carateres*/
        sprintf(bloc_chiffre_en_char,"%ld",bloc_c );
        strcat(password_chiffre,bloc_chiffre_en_char);
    }

    return 1;
}


/*supprime la ligne avec le login fourni et ajoute une ligne utilisateur a la fin avec les infos fournis*/
int supprimer_et_ajouter_ligne_utilisateur(User u){
    FILE *f_users=fopen("./save/users.json","r");
    FILE *f_temp=fopen("./save/temp_users.json","w");
    if (f_users!=NULL && f_temp!=NULL){
        char motRech[40]="\"login\": \"";
        strcat(motRech,u->login);
        motRech[strlen(motRech)]='\"';
        motRech[strlen(motRech)]='\0';
        char ligne[300];
        while (fgets(ligne,300,f_users) != NULL && ligne[strlen(ligne)-2]!='}') {
            if (strstr(ligne,motRech)==NULL){
                fputs(ligne,f_temp);
            }

        }
        if(strstr(ligne,motRech)==NULL){
            ligne[strlen(ligne)-1]='\0';
            fputs(ligne,f_temp);
            fprintf(f_temp, ",\n");
        }
        fprintf(f_temp,"{ \"login\": \"%s\", \"password\": \"%s\", \"statut\": %d, \"nom\": \"%s\", \"prenom\": \"%s\", \"email\": \"%s\" }\n]\n",u->login,u->password,u->s,u->nom,u->prenom,u->email);
        fclose(f_users);
        fclose(f_temp);
        remove("./save/users.json");
        rename("./save/temp_users.json","./save/users.json");
        return 1;
    }
    return 0;

}


/*supprime une ligne du fichier utilisateur s'il s'agit de la derniere enleve la virgule de la ligne precedente pour que le fichier reste compatible json
retourn 1 s'il a reussi(fichier ouvert/fichier temp cree) et 0 sinon*/
int supprimer_ligne_users(char *login){
    FILE *fichier_users=fopen("./save/users.json","r");
    FILE *f_temp=fopen("./save/temp_users.json","w");

    if(fichier_users!=NULL && f_temp!=NULL){
        char motRech[40]="\"login\": \"";
        strcat(motRech,login);
        motRech[strlen(motRech)]='\"';
        motRech[strlen(motRech)]='\0';
        char ligne[300];
        char ligne_1[300];
        fgets(ligne,300,fichier_users);
        while (fgets(ligne_1,300,fichier_users) != NULL) {
            if ((strstr(ligne_1, motRech) != NULL) && (ligne_1[strlen(ligne_1)-2]=='}')) {
                if (ligne[0]=='[')
                    fputs(ligne,f_temp);
                else{
                    ligne[strlen(ligne)-2]='\n';
                    ligne[strlen(ligne)-1]='\0';
                    fputs(ligne,f_temp);
                }
            }
            else if(strstr(ligne,motRech)==NULL){
                fputs(ligne,f_temp);
            }
            strcpy(ligne,ligne_1);
        }
        fputs(ligne,f_temp);
        fclose(fichier_users);
        fclose(f_temp);
        remove("./save/users.json");
        rename("./save/temp_users.json","./save/users.json");
        return 1;
    }
    return 0;
}


/* Recherche un login dans le fichier user.json
retourne la ligne comportant toute les donnes du login dans ligne_retournee passee en parametre */
int recherche_login_renvoie_ligne(char *login, char *ligne_retournee){
    FILE *fichier_users=fopen("./save/users.json","r");
    if(fichier_users!=NULL){
        char motRech[40]="\"login\": \"";
        strcat(motRech,login);
        motRech[strlen(motRech)]='\"';
        motRech[strlen(motRech)]='\0';
        char ligne[300];
        while (fgets(ligne,300,fichier_users) != NULL) {
            if (strstr(ligne, motRech) != NULL){
                strcpy(ligne_retournee,ligne);
            }
        }
        fclose(fichier_users);
        return 1;
    }
    return 0;
}


/*ajoute une ligne utilisateur a la fin du fichier en prenant garde de garder la bonne mise en forme*/
int ajout_ligne_utilisateur(User u){
    FILE *f_users=fopen("./save/users.json","r");
    FILE *f_temp=fopen("./save/temp_users.json","w");
    if (f_users!=NULL && f_temp !=NULL){
        char ligne[300];
        while(fgets(ligne,300,f_users)!=NULL && (ligne[strlen(ligne)-2]!='}' && ligne[strlen(ligne)-2]!=']')){
            fputs(ligne,f_temp);
        }
        if (ligne[strlen(ligne)-2]=='}'){
            ligne[strlen(ligne)-1]='\0';
            fputs(ligne,f_temp);
            fprintf(f_temp,",\n");
        }
        fprintf(f_temp,"{ \"login\": \"%s\", \"password\": \"%s\", \"statut\": %d, \"nom\": \"%s\", \"prenom\": \"%s\", \"email\": \"%s\" }\n]\n",u->login,u->password,u->s,u->nom,u->prenom,u->email);
        fclose(f_users);
        fclose(f_temp);
        remove("./save/users.json");
        rename("./save/temp_users.json","./save/users.json");
        return 1;
    }
    return 0;
}


/* recherche si le login existe deja dans le fichier users.json  (indication pour francois 1ms de moyenne)
renvoie 1 s'il existe deja, 0 s'il  n''existe pas et -1 s'il y a un probleme avec le fichier*/
int recherche_occurence_login(char *login){
    FILE *fichier_users=fopen("./save/users.json","r");

    int occurence=0;
    if (!fichier_users){ // gestion d'erreur ?
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    else {
        char motRech[40]="\"login\": \"";
        strcat(motRech,login);
        motRech[strlen(motRech)]='\"';
        motRech[strlen(motRech)]='\0';
        char ligne[300];
        while (fgets(ligne,300,fichier_users) != NULL) {
            if (strstr(ligne, motRech) != NULL){
                occurence=1;
            }
        }
        fclose(fichier_users);
    }
    return occurence;
}


/*creer un fichier .json avec le nom du login dans le dossier historique pour creer l'historique de l'utilisateur et l'initialise
Renvoie 1 si elle a foncionner correctement (si le fichier s'est creer) sinon 0*/
int creation_fichier_historique_utilisateur(char *login){
    char nom_fichier[40]="./save/historique/";
    strcat(nom_fichier,login);
    strcat(nom_fichier,".json");
    FILE *new_file_histo=fopen(nom_fichier,"w");
    if (new_file_histo!=NULL){
        fprintf(new_file_histo,"{\n\"emprunter\": [\n{\"id\": 0,\"nom\": \"exemple\",\"du\": \"date debut\",\"au\": \"date de fin\",\"rendu\": 1,\"proprietaire\": \"ici son login\"}\n],\n\"preter\": [\n{\"id\": 1,\"nom\": \"exemple\",\"du\": \"date debut\",\"au\": \"date de fin\",\"rendu\": 1,\"beneficiaire\": \"ici son login\"}\n]\n}\n");
        fclose(new_file_histo);
        return 1;
    }
    return 0;

}

