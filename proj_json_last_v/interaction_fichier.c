#include "interaction_fichier.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*creer un fichier .json avec le nom du login dans le dossier historique pour creer l'historique de l'utilisateur et l'initialise
Renvoie 1 si elle a foncionner correctement (si le fichier s'est creer) sinon 0*/
int creation_fichier_historique_utilisateur(char *login){
    char nom_fichier[40]="./save/historique/";
    strcat(nom_fichier,login);
    strcat(nom_fichier,".json");
    FILE *new_file_histo=fopen(nom_fichier,"w");
    if (new_file_histo!=NULL){
        fprintf(new_file_histo,"{\n\"emprunter\": [],\n\"preter\": []\n}");
        fclose(new_file_histo);
        return 1;
    }
    return 0;

}

/*ajoute une ligne ressource a la fin du fichier en prenant garde de garder la bonne mise en forme*/
int ajout_ligne_ressource(int id,char *nom,char *description,int type,int en_pret,char *proprietaire,char *beneficiaire) {
    FILE *f_ressources=fopen("./save/ressources.json","r");
    FILE *f_temp=fopen("./save/temp_ajout_ressources.json","w");
    if (f_ressources!=NULL && f_temp !=NULL){
        char ligne[300];
        while(fgets(ligne,300,f_ressources)!=NULL && (ligne[strlen(ligne)-2]!='}' && ligne[strlen(ligne)-2]!=']')){
            fputs(ligne,f_temp);
        }
        if (ligne[strlen(ligne)-2]=='}'){
            ligne[strlen(ligne)-1]='\0';
            fputs(ligne,f_temp);
            fprintf(f_temp,",\n");
        }
        fprintf(f_temp,"{ \"id\": %d, \"nom\": \"%s\", \"description\": \"%s\", \"type\": %d, \"en_pret\": %d, \"proprietaire\": \"%s\", \"beneficiaire\": \"%s\" }\n]\n",id,nom,description,type,en_pret,proprietaire,beneficiaire);
        fclose(f_ressources);
        fclose(f_temp);
        remove("./save/ressources.json");
        rename("./save/temp_ajout_ressources.json","./save/ressources.json");
        return 1;
    }
    return 0;
}

/*ajoute une ligne utilisateur a la fin du fichier en prenant garde de garder la bonne mise en forme*/
int ajout_ligne_utilisateur(char *login, char *password, int statut, char *nom, char *prenom, char *email){
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
        fprintf(f_temp,"{ \"login\": \"%s\", \"password\": \"%s\", \"statut\": %d, \"nom\": \"%s\", \"prenom\": \"%s\", \"email\": \"%s\" }\n]\n",login,password,statut,nom,prenom,email);
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

/*supprime une ligne du fichier ressources s'il s'agit de la derniere enleve la virgule de la ligne precedente pour que le fichier reste compatible json
retourn 1 s'il a reussi(fichier ouvert/fichier tempcree) et 0 sinon*/
int supprimer_ligne_ressource(int id){
    FILE *fichier_ressources=fopen("./save/ressources.json","r");
    FILE *f_temp=fopen("./save/temp_ressources.json","w");


    if(fichier_ressources!=NULL && f_temp!=NULL){
        char motRech[40]="\"id\": ";
        char char_id[10];
        sprintf(char_id,"%d",id);
        strcat(motRech,char_id);
        motRech[strlen(motRech)]=',';
        motRech[strlen(motRech)]='\0';
        printf("%s\n",motRech );
        char ligne[300];
        char ligne_1[300];
        fgets(ligne,300,fichier_ressources);
        while (fgets(ligne_1,300,fichier_ressources) != NULL) {
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
        fclose(fichier_ressources);
        fclose(f_temp);
        remove("./save/ressources.json");
        rename("./save/temp_ressources.json","./save/ressources.json");
        return 1;
    }
    return 0;
}


/*supprime la ligne avec le login fourni et ajoute une ligne utilisateur a la fin avec les infos fournis*/
int supprimer_et_ajouter_ligne_utilisateur(char *login, char *password, int statut, char *nom, char *prenom, char *email){
    FILE *f_users=fopen("./save/users.json","r");
    FILE *f_temp=fopen("./save/temp_users.json","w");
    if (f_users!=NULL && f_temp!=NULL){
        char motRech[40]="\"login\": \"";
        strcat(motRech,login);
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
        fprintf(f_temp,"{ \"login\": \"%s\", \"password\": \"%s\", \"statut\": %d, \"nom\": \"%s\", \"prenom\": \"%s\", \"email\": \"%s\" }\n]\n",login,password,statut,nom,prenom,email);
        fclose(f_users);
        fclose(f_temp);
        remove("./save/users.json");
        rename("./save/temp_users.json","./save/users.json");
        return 1;
    }
    return 0;

}

/*supprime la ligne avec l id fourni et la modifie avec les elements fournis et ajoute la ligne modifie a la fin*/
int supprimer_et_ajouter_ligne_ressource(int id,char *nom,char *description,int type,int en_pret,char *proprietaire,char *beneficiaire){//attention id char ou int
    FILE *f_ressources=fopen("./save/ressources.json","r");
    FILE *f_temp=fopen("./save/temp_ajout_ressources.json","w");
    if (f_ressources!=NULL && f_temp!=NULL){
        char motRech[40]="\"id\": ";
        char id_char[10];
        sprintf(id_char,"%d",id);
        strcat(motRech,id_char);
        motRech[strlen(motRech)]=',';
        motRech[strlen(motRech)]='\0';
        char ligne[300];
        while (fgets(ligne,300,f_ressources) != NULL && ligne[strlen(ligne)-2]!='}') {
            if (strstr(ligne,motRech)==NULL){
                fputs(ligne,f_temp);
            }

        }
        if(strstr(ligne,motRech)==NULL){
            ligne[strlen(ligne)-1]='\0';
            fputs(ligne,f_temp);
            fprintf(f_temp, ",\n");
        }
        fprintf(f_temp,"{ \"id\": %d, \"nom\": \"%s\", \"description\": \"%s\", \"type\": %d, \"en_pret\": %d, \"proprietaire\": \"%s\", \"beneficiaire\": \"%s\" }\n]\n",id,nom,description,type,en_pret,proprietaire,beneficiaire);
        fclose(f_ressources);
        fclose(f_temp);
        remove("./save/ressources.json");
        rename("./save/temp_ajout_ressources.json","./save/ressources.json");
        return 1;
    }
    return 0;


}
