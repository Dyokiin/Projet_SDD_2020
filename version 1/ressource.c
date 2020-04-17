#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>
#include <time.h>
#include "ressource.h"



#define LONGEUR_LIGNE 300
#define TAILLE_NORMAL 22
#define TAILLE_DESCRIPTION 44

enum type { VEHICULE, LIVRE, DVD, PLANTE};


struct s_objet{
    long int id;
    char *nom;
    char *description;
    enum type t;
    int en_pret;
    char *proprietaire;
    char *beneficiaire;
};


int type_atoi(char *type){
    if (strcmp(type,"Vehicule")==0){
        return 1;
    }
    if (strcmp(type,"Livre")==0){
        return 2;
    }
    if (strcmp(type,"DVD")==0){
        return 3;
    }
    return 4;
}


int nb_ressource_empruntable_type(char *login,char *type) {
    int tp=type_atoi(type);
    FILE *fichier=fopen("./save/ressources.json","r");
    Objet o=malloc(sizeof(struct s_objet));
    o->nom=(char *)malloc(sizeof(char)*TAILLE_NORMAL);
    o->description=(char *)malloc(sizeof(char)*TAILLE_DESCRIPTION);
    o->proprietaire=(char *)malloc(sizeof(char)*TAILLE_NORMAL);
    o->beneficiaire=(char *)malloc(sizeof(char)*TAILLE_NORMAL);

    if (fichier==NULL || o==NULL || o->nom==NULL || o->description==NULL || o->proprietaire==NULL || o->beneficiaire==NULL){
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    char ligne[LONGEUR_LIGNE];
    fgets(ligne,LONGEUR_LIGNE,fichier);
    fgets(ligne,LONGEUR_LIGNE,fichier);
    int compteur=0;
    while (ligne[strlen(ligne)-2]!=']') {
        transforme_ligne_ressource_en_sa_structure(ligne,o);
        if (!o->en_pret && o->t==tp && strcmp(o->proprietaire,login)!=0){
            compteur++;
        }
        fgets(ligne,300,fichier);
    }
    free(o->nom);
    free(o->description);
    free(o->proprietaire);
    free(o->beneficiaire);
    free(o);
    fclose(fichier);
    return compteur;
}

int renvoyer_ressource_type(char *login,char *type, int numero, char *ligne_retournee){
    int tp=type_atoi(type);
    FILE *fichier=fopen("./save/ressources.json","r");
    Objet o=malloc(sizeof(struct s_objet));
    o->nom=(char *)malloc(sizeof(char)*TAILLE_NORMAL);
    o->description=(char *)malloc(sizeof(char)*TAILLE_DESCRIPTION);
    o->proprietaire=(char *)malloc(sizeof(char)*TAILLE_NORMAL);
    o->beneficiaire=(char *)malloc(sizeof(char)*TAILLE_NORMAL);

    if (fichier==NULL || o==NULL || o->nom==NULL || o->description==NULL || o->proprietaire==NULL || o->beneficiaire==NULL){
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    char ligne[LONGEUR_LIGNE];
    fgets(ligne,LONGEUR_LIGNE,fichier);
    fgets(ligne,LONGEUR_LIGNE,fichier);
    int compteur=0;
    int trouve=0;
    while (ligne[strlen(ligne)-2]!=']' && trouve==0) {
        transforme_ligne_ressource_en_sa_structure(ligne,o);
        if (!o->en_pret && o->t==tp && strcmp(o->proprietaire,login)!=0){
            compteur++;
            if(compteur==numero){
                strcpy(ligne_retournee,ligne);
                trouve=1;
            }
        }
        fgets(ligne,300,fichier);
    }
    free(o->nom);
    free(o->description);
    free(o->proprietaire);
    free(o->beneficiaire);
    free(o);
    fclose(fichier);
    return trouve;

}

int emprunter_ressource_type(char *login,char *type,int numero){
    int tp=type_atoi(type);
    FILE *fichier=fopen("./save/ressources.json","r");
    Objet o=malloc(sizeof(struct s_objet));
    o->nom=(char *)malloc(sizeof(char)*TAILLE_NORMAL);
    o->description=(char *)malloc(sizeof(char)*TAILLE_DESCRIPTION);
    o->proprietaire=(char *)malloc(sizeof(char)*TAILLE_NORMAL);
    o->beneficiaire=(char *)malloc(sizeof(char)*TAILLE_NORMAL);

    if (fichier==NULL || o==NULL || o->nom==NULL || o->description==NULL || o->proprietaire==NULL || o->beneficiaire==NULL){
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    char ligne[LONGEUR_LIGNE];
    fgets(ligne,LONGEUR_LIGNE,fichier);
    fgets(ligne,LONGEUR_LIGNE,fichier);
    int compteur=0;
    int trouve=0;
    while (ligne[strlen(ligne)-2]!=']' && trouve==0) {
        transforme_ligne_ressource_en_sa_structure(ligne,o);
        if (!o->en_pret && o->t==tp && strcmp(o->proprietaire,login)!=0){
            compteur++;
            if(compteur==numero){
                trouve=1;
            }
        }
        fgets(ligne,300,fichier);
    }
    strcpy(o->beneficiaire,login);
    fclose(fichier);
    emprunter(o);

    free(o->nom);
    free(o->description);
    free(o->proprietaire);
    free(o->beneficiaire);
    free(o);

    return trouve;

}

int emprunter(Objet o){
    o->en_pret=1;
    supprimer_et_ajouter_ligne_ressource(o);
    ajouter_ligne_preter(o);
    ajouter_ligne_emprunter(o);
    return 1;
}


/*supprime la ligne avec l id fourni et la modifie avec les elements fournis et ajoute la ligne modifie a la fin*/
int supprimer_et_ajouter_ligne_ressource(Objet o){
    FILE *f_ressources=fopen("./save/ressources.json","r");
    FILE *f_temp=fopen("./save/temp_ajout_ressources.json","w");
    if (f_ressources!=NULL && f_temp!=NULL){
        char motRech[20]="{ \"id\": ";
        char id_char[11];
        sprintf(id_char,"%ld",o->id);
        strcat(motRech,id_char);
        strcat(motRech,",");
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

        fprintf(f_temp,"{ \"id\": %ld, \"nom\": \"%s\", \"description\": \"%s\", \"type\": %d, \"en_pret\": %d, \"proprietaire\": \"%s\", \"beneficiaire\": \"%s\" }\n]\n",o->id,o->nom,o->description,o->t,o->en_pret,o->proprietaire,o->beneficiaire);
        fclose(f_ressources);
        fclose(f_temp);
        remove("./save/ressources.json");
        rename("./save/temp_ajout_ressources.json","./save/ressources.json");
        return 1;
    }
    return 0;


}

// Ecrire dans l'historique

int ajouter_ligne_emprunter(Objet o){
    char nom_fichier[]="./save/historique/";
    strcat(nom_fichier,o->beneficiaire);
    strcat(nom_fichier,".json");
    FILE *f_histo=fopen(nom_fichier,"r");
    FILE *f_temp=fopen("./save/historique/temp_preter.json","w");
    if (f_histo!=NULL && f_temp!=NULL){
        char ligne[300];
        fgets(ligne,300,f_histo);
        while (ligne[strlen(ligne)-2]!='}') {
            fputs(ligne,f_temp);
            fgets(ligne,300,f_histo);
        }
        ligne[strlen(ligne)-1]='\0';
        fputs(ligne,f_temp);
        time_t t = time(NULL);
        char date[25];
        strftime(date, sizeof(date), "%d-%m-%Y - %X", localtime(&t));
        fprintf(f_temp, ",\n{\"id\": %ld,\"nom\": \"%s\",\"du\": \"%s\",\"au\": \"\",\"rendu\": 0,\"proprietaire\": \"%s\"}\n",o->id,o->nom,date,o->proprietaire);

        while (fgets(ligne,300,f_histo)!=NULL) {
            fputs(ligne,f_temp);
        }

        fclose(f_histo);
        fclose(f_temp);
        remove(nom_fichier);
        rename("./save/historique/temp_preter.json",nom_fichier);
        return 1;
    }
    return 0;

}


int ajouter_ligne_preter(Objet o){
    char nom_fichier[]="./save/historique/";
    strcat(nom_fichier,o->proprietaire);
    strcat(nom_fichier,".json");
    FILE *f_histo=fopen(nom_fichier,"r");
    FILE *f_temp=fopen("./save/historique/temp_emprunter.json","w");
    if (f_histo!=NULL && f_temp!=NULL){
        char ligne[300];
        fgets(ligne,300,f_histo);
        int compteur=0;
        while (compteur!=2) {
            fputs(ligne,f_temp);
            fgets(ligne,300,f_histo);
            if(ligne[strlen(ligne)-2]=='}'){
                compteur++;
            }
        }
        ligne[strlen(ligne)-1]='\0';
        fputs(ligne,f_temp);
        time_t t = time(NULL);
        char date[25];
        strftime(date, sizeof(date), "%d-%m-%Y - %X", localtime(&t));
        fprintf(f_temp, ",\n{\"id\": %ld,\"nom\": \"%s\",\"du\": \"%s\",\"au\": \"\",\"rendu\": 0,\"beneficiaire\": \"%s\"}\n]\n}\n",o->id,o->nom,date,o->beneficiaire);

        fclose(f_histo);
        fclose(f_temp);
        remove(nom_fichier);
        rename("./save/historique/temp_emprunter.json",nom_fichier);
        return 1;
    }
    return 0;
}

int transforme_ligne_ressource_en_sa_structure(char *ligne,Objet o){

    struct json_object *parsed_json;
    struct json_object *nom;
    struct json_object *description;
    struct json_object *t;
    struct json_object *en_pret;
    struct json_object *proprietaire;
    struct json_object *beneficiaire;
    struct json_object *id;


    parsed_json = json_tokener_parse(ligne);

    json_object_object_get_ex(parsed_json, "id", &id);
    json_object_object_get_ex(parsed_json, "nom", &nom);
    json_object_object_get_ex(parsed_json, "description", &description);
    json_object_object_get_ex(parsed_json, "type", &t);
    json_object_object_get_ex(parsed_json, "en_pret", &en_pret);
    json_object_object_get_ex(parsed_json, "proprietaire", &proprietaire);
    json_object_object_get_ex(parsed_json, "beneficiaire", &beneficiaire);

    o->id=json_object_get_int64(id);
    strcpy(o->nom,json_object_get_string(nom));
    strcpy(o->description,json_object_get_string(description));
    o->t=json_object_get_int(t);
    o->en_pret=json_object_get_int(en_pret);
    strcpy(o->proprietaire,json_object_get_string(proprietaire));
    strcpy(o->beneficiaire,json_object_get_string(beneficiaire));
    return 1;
}


int trouve_caractere_speciaux_ressource(char *chaine){
	for(int i=0;i<strlen(chaine);i++){
		if (chaine[i]<32 || chaine[i]>126 || chaine[i]=='"' || chaine[i]=='\\' || chaine[i]=='/'){
			return 1;
		}
	}
	return 0;
}



int new_ressource (char *nom,char * description, char *login,int type){
    if(trouve_caractere_speciaux_ressource(nom) || trouve_caractere_speciaux_ressource(description)){
        return 1;
    }
    Objet o=(Objet)malloc(sizeof(struct s_objet));
    o->nom=(char *)malloc(sizeof(char)*22);
    o->description=(char *)malloc(sizeof(char)*42);
    o->proprietaire=(char *)malloc(sizeof(char)*22);
    o->beneficiaire=(char *)malloc(sizeof(char)*3);

    if(o==NULL || o->nom==NULL || o->description==NULL || o->proprietaire==NULL || o->beneficiaire==NULL){
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    strcpy(o->nom,nom);
    strcpy(o->description,description);
    strcpy(o->beneficiaire,"");
    strcpy(o->proprietaire,login);
    o->en_pret=0;
    o->id=time(NULL);
    o->t=type;
    ajout_ligne_ressource(o);
    free(o->nom);
    free(o->description);
    free(o->proprietaire);
    free(o->beneficiaire);
    free(o);

    return 0;
}

/*ajoute une ligne ressource a la fin du fichier en prenant garde de garder la bonne mise en forme*/
int ajout_ligne_ressource(Objet o) {
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
        fprintf(f_temp,"{ \"id\": %ld, \"nom\": \"%s\", \"description\": \"%s\", \"type\": %d, \"en_pret\": %d, \"proprietaire\": \"%s\", \"beneficiaire\": \"%s\" }\n]\n",o->id,o->nom,o->description,o->t,o->en_pret,o->proprietaire,o->beneficiaire);
        fclose(f_ressources);
        fclose(f_temp);
        remove("./save/ressources.json");
        rename("./save/temp_ajout_ressources.json","./save/ressources.json");
        return 1;
    }
    return 0;
}


int nb_mes_ressources(char *login) {
    FILE *fichier=fopen("./save/ressources.json","r");
    Objet o=malloc(sizeof(struct s_objet));
    o->nom=(char *)malloc(sizeof(char)*TAILLE_NORMAL);
    o->description=(char *)malloc(sizeof(char)*TAILLE_DESCRIPTION);
    o->proprietaire=(char *)malloc(sizeof(char)*TAILLE_NORMAL);
    o->beneficiaire=(char *)malloc(sizeof(char)*TAILLE_NORMAL);

    if (fichier==NULL || o==NULL || o->nom==NULL || o->description==NULL || o->proprietaire==NULL || o->beneficiaire==NULL){
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    char ligne[LONGEUR_LIGNE];
    fgets(ligne,LONGEUR_LIGNE,fichier);
    fgets(ligne,LONGEUR_LIGNE,fichier);
    int compteur=0;
    while (ligne[strlen(ligne)-2]!=']') {
        transforme_ligne_ressource_en_sa_structure(ligne,o);
        if (strcmp(o->proprietaire,login)==0){
            compteur++;
        }
        fgets(ligne,300,fichier);
    }
    free(o->nom);
    free(o->description);
    free(o->proprietaire);
    free(o->beneficiaire);
    free(o);
    fclose(fichier);
    return compteur;
}


int afficher_mes_ressources(char *login, char *ligne_retournee,int numero){
    FILE *fichier=fopen("./save/ressources.json","r");
    Objet o=malloc(sizeof(struct s_objet));
    o->nom=(char *)malloc(sizeof(char)*TAILLE_NORMAL);
    o->description=(char *)malloc(sizeof(char)*TAILLE_DESCRIPTION);
    o->proprietaire=(char *)malloc(sizeof(char)*TAILLE_NORMAL);
    o->beneficiaire=(char *)malloc(sizeof(char)*TAILLE_NORMAL);

    if (fichier==NULL || o==NULL || o->nom==NULL || o->description==NULL || o->proprietaire==NULL || o->beneficiaire==NULL){
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    char ligne[LONGEUR_LIGNE];
    fgets(ligne,LONGEUR_LIGNE,fichier);
    fgets(ligne,LONGEUR_LIGNE,fichier);
    int compteur=0;
    int trouve=0;
    while (ligne[strlen(ligne)-2]!=']' && trouve==0) {
        transforme_ligne_ressource_en_sa_structure(ligne,o);
        if (strcmp(o->proprietaire,login)==0){
            compteur++;
            if(compteur==numero){
                strcpy(ligne_retournee,ligne);
                trouve=1;
            }
        }
        fgets(ligne,300,fichier);
    }
    free(o->nom);
    free(o->description);
    free(o->proprietaire);
    free(o->beneficiaire);
    free(o);
    fclose(fichier);
    return trouve;

}

/*supprime rssource renvoi 0 si ressource supprime et 1 si ressource non supprime car en pret*/
int supprimer_ressource(char *login,int numero){
    FILE *fichier=fopen("./save/ressources.json","r");
    Objet o=malloc(sizeof(struct s_objet));
    o->nom=(char *)malloc(sizeof(char)*TAILLE_NORMAL);
    o->description=(char *)malloc(sizeof(char)*TAILLE_DESCRIPTION);
    o->proprietaire=(char *)malloc(sizeof(char)*TAILLE_NORMAL);
    o->beneficiaire=(char *)malloc(sizeof(char)*TAILLE_NORMAL);

    if (fichier==NULL || o==NULL || o->nom==NULL || o->description==NULL || o->proprietaire==NULL || o->beneficiaire==NULL){
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    char ligne[LONGEUR_LIGNE];
    fgets(ligne,LONGEUR_LIGNE,fichier);
    fgets(ligne,LONGEUR_LIGNE,fichier);
    int compteur=0;
    int trouve=0;
    while (ligne[strlen(ligne)-2]!=']' && trouve==0) {
        transforme_ligne_ressource_en_sa_structure(ligne,o);
        if (strcmp(o->proprietaire,login)==0){
            compteur++;
            if(compteur==numero){
                trouve=1;
            }
        }
        fgets(ligne,300,fichier);
    }
    fclose(fichier);
    int retour=1;
    if(!o->en_pret){
        supprimer_ligne_ressource(o->id);
        retour=0;
    }


    free(o->nom);
    free(o->description);
    free(o->proprietaire);
    free(o->beneficiaire);
    free(o);

    return retour;

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
