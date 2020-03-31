#include "interaction_fichier.h"
#include <stdio.h>
#include <string.h>
#include <json-c/json.h>


int main(int argc, char *argv[]) {
    /*char login[]="mouahah";
    char password[]="1234567890";
    ajout_ligne_utilisateur(login,password);*/
    /*char nom[]="television 4K";
    char description[]="je suis une televion en carton";
    int type=14;
    char login[]="philoudu69";
    creation_ressource2(nom,description,type,login);
    printf("ok\n");*/
    //char login[]="mouahah";
    //printf("%d\n", recherche_occurence_login(login));
    //printf("%d\n", recherche_occurence_login(login));
    /*char ligne[300];
    char login[]="phil";
    printf("%d\n",recherche_login_renvoie_ligne(login,ligne) );
    printf("%s\n",ligne );
    printf("%d\n",supprimer_ligne_users(login) );*/
    return 0;
}


/* Ajoute, dans le fichier users.json une ligne utilisateur avec login/password et statut a BASIC(0), met a null les autres infos (nom,prenom,email)
Et creer un fichier .json avec le nom du login dans le dossier historique pour creer l'historique de l'utilisateur
Renvoie 1 si elle a foncionner correctement (si le fichier s'est ouvert) sinon 0*/
int ajout_ligne_utilisateur_et_fichier_historique(char *login,char *password){
    char nom_fichier[40]="./save/historique/";
    strcat(nom_fichier,login);
    strcat(nom_fichier,".json");
    FILE *temp=fopen("./save/temp_users.json","w");
    FILE *ancien=fopen("./save/users.json","r");
    FILE *new_file_histo=fopen(nom_fichier,"w");
    if (temp!=NULL && ancien !=NULL && new_file_histo!=NULL){
        struct json_object *tableau;
        struct json_object *valeur_tableau;
        fseek(ancien,0L,SEEK_END);
        int taille_fichier=ftell(ancien);
        fseek(ancien,0,SEEK_SET);
        char *buffer=(char *)malloc(sizeof(char)*(taille_fichier));
        fread(buffer,taille_fichier,1,ancien);
        fclose(ancien);
        tableau = json_tokener_parse(buffer);
        free(buffer);
        fprintf(temp,"[");
        for(long unsigned int i=0;i<json_object_array_length(tableau);i++) {
    		valeur_tableau = json_object_array_get_idx(tableau, i);
    		fprintf(temp,"\n%s,",json_object_get_string(valeur_tableau));
    	}
        fprintf(temp,"\n{ \"login\": \"%s\", \"password\": \"%s\", \"statut\": 0, \"nom\": null, \"prenom\": null, \"email\": null }\n]\n",login,password);
        fprintf(new_file_histo,"{\n\"emprunter\": [],\n\"preter\": []\n}");
        fclose(temp);
        fclose(new_file_histo);
        remove("./save/users.json");
        rename("./save/temp_users.json","./save/users.json");
        return 1;

    }
    return 0;
}


/* Ajoute dans le fichier ressources.json une nouvelle ressources qui est un objet JSON prend un entrer le nom, le type, la description
Renvoie 1 si elle a foncionner correctement (si le fichier s'est ouvert) sinon 0 */
int creation_ressource(char *nom,char *description,int type,char *login){
    FILE *f_ressource=fopen("./save/ressources.json","r");
    FILE *temp=fopen("./save/temp_ressources.json","w");
    if (temp!=NULL && f_ressource!=NULL){
        struct json_object *tableau_liste_objets_ressources;
        struct json_object *objet_ressouce;
        fseek(f_ressource,0L,SEEK_END);
        int taille_fichier=ftell(f_ressource);
        fseek(f_ressource,0,SEEK_SET);
        char *buffer=(char *)malloc(sizeof(char)*(taille_fichier));
        fread(buffer,taille_fichier,1,f_ressource);
        fclose(f_ressource);
        tableau_liste_objets_ressources = json_tokener_parse(buffer);
        free(buffer);
        fprintf(temp,"[");
        for(long unsigned int i=0;i<json_object_array_length(tableau_liste_objets_ressources);i++) {
    		objet_ressouce = json_object_array_get_idx(tableau_liste_objets_ressources, i);
    		fprintf(temp,"\n%s,",json_object_get_string(objet_ressouce));
    	}
        fprintf(temp,"\n{ \"nom\": \"%s\", \"description\": \"%s\", \"type\": %d, \"en_pret\": false, \"proprietaire\": \"%s\" }\n]\n",nom,description,type,login);
        fclose(temp);
        remove("./save/ressources.json");
        rename("./save/temp_ressources.json","./save/ressources.json");

        return 1;

    }
    return 0;
}

/* meme fonction que creation_ressource sans utiliser la lib json-c beaucoup plus rapide en temps d'execution*/
int creation_ressource2(char *nom,char *description,int type,char *login){
    FILE *fichier=fopen("./save/ressources.json","r");
    FILE *temp=fopen("./save/temp","w");
    if (fichier!=NULL && temp!=NULL){
        char ligne[300];
        fgets(ligne,300,fichier);
        fputs(ligne,temp);
        while(fgets(ligne,300,fichier)!=NULL && ligne[strlen(ligne)-2]==','){ //-2 car \0 et \n

            fputs(ligne,temp);
        }
        ligne[strlen(ligne)-1]='\0';
        fputs(ligne,temp);
        fprintf(temp,",\n{ \"nom\": \"%s\", \"description\": \"%s\", \"type\": %d, \"en_pret\": false, \"proprietaire\": \"%s\", \"beneficiaire\": null, \"id\": 45}\n]\n",nom,description,type,login);
        fclose(temp);
        fclose(fichier);
        remove("./save/ressources.json");
        rename("./save/temp","./save/ressources.json");
        return 1;
    }
    return 0;
}

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
int ajout_ligne_ressource(int id,char *nom,char *description,int type,int en_pret,char *proprietaire,char *beneficiaire){
    FILE *f_ressources=fopen("./save/ressources.json","r");
    FILE *f_temp=fopen("./save/temp_ajout_ressources.json","w");
    if (f_ressources!=NULL && f_temp !=NULL){
        char ligne[300];
        while(fgets(ligne,300,f_ressources)!=NULL &&ligne[strlen(ligne)-2]!='}'){
            fputs(ligne,f_temp);
        }
        ligne[strlen(ligne)-1]='\0';
        fputs(ligne,f_temp);
        fprintf(f_temp,",\n{ \"id\": %d, \"nom\": \"%s\", \"description\": \"%s\", \"type\": %d, \"en_pret\": %d, \"proprietaire\": \"%s\", \"beneficiaire\": %s }\n]\n",id,nom,description,type,en_pret,proprietaire,beneficiaire);
        fclose(f_ressource);
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
    FILE *f_temp=fopen("./save/temp_ajout_users.json","w");
    if (f_users!=NULL && f_temp !=NULL){
        char ligne[300];
        while(fgets(ligne,300,f_users)!=NULL &&ligne[strlen(ligne)-2]!='}'){
            fputs(ligne,f_temp);
        }
        ligne[strlen(ligne)-1]='\0';
        fputs(ligne,f_temp);
        fprintf(f_temp,",\n{ \"login\": \"%s\", \"password\": \"%s\", \"statut\": %d, \"nom\": %s, \"prenom\": %s, \"email\": %s }\n]\n",login,password,statut,nom,prenom,email);
        fclose(f_users);
        fclose(f_temp);
        remove("./save/users.json");
        rename("./save/temp_ajout_users.json","./save/users.json");
        return 1;
    }
    return 0;
}

/* recherche si le login existe deja dans le fichier users.json  (indication pour francois 1ms de moyenne)
renvoie 1 s'il existe deja, 0 s'il  n''existe pas et -1 s'il y a un probleme avec le fichier*/
int recherche_occurence_login(char *login){
    FILE *fichier_users=fopen("./save/users.json","r");

    int occurence=0;
    if (!fichier_users){ // Il faut gerer l'erreur differement
        printf("ERREUR: Impossible d'ouvrir le fichier ou fichier inexistant.\n");
        occurence=-1;
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
                ligne[strlen(ligne)-2]='\n';
                ligne[strlen(ligne)-1]='\0';
                fputs(ligne,f_temp); //modifier
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
int supprimer_ligne_ressource(char *id){  //transformer id en int peut etre ?
    FILE *fichier_ressources=fopen("./save/ressources.json","r");
    FILE *f_temp=fopen("./save/temp_ressources.json","w");


    if(fichier_ressources!=NULL && f_temp!=NULL){
        char motRech[40]="\"id\": \"";
        strcat(motRech,id);
        motRech[strlen(motRech)]='\"';
        motRech[strlen(motRech)]='\0';
        char ligne[300];
        char ligne_1[300];
        fgets(ligne,300,fichier_ressources);
        while (fgets(ligne_1,300,fichier_ressources) != NULL) {
            if ((strstr(ligne_1, motRech) != NULL) && (ligne_1[strlen(ligne_1)-2]=='}')) {
                ligne[strlen(ligne)-2]='\n';
                ligne[strlen(ligne)-1]='\0';
                fputs(ligne,f_temp); //modifier
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
