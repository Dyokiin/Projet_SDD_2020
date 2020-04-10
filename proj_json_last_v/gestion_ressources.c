#include "gestion_ressources.h"
#include "lecture.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>
#include <time.h>

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




int nouvelle_ressource(char *login){
    Objet o=(Objet)malloc(sizeof(struct s_objet));
    o->nom=(char *)malloc(sizeof(char)*20);
    o->description=(char *)malloc(sizeof(char)*40);
    o->proprietaire=(char *)malloc(sizeof(char)*20);
    o->beneficiaire=(char *)malloc(sizeof(char)*3);

    if(o==NULL || o->nom==NULL || o->description==NULL || o->proprietaire==NULL || o->beneficiaire==NULL){
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    printf("Saisir 'q' pour revenir au menu. Votre nom de ressource doit etre de taille min 4 et max . Ne pas contenir : d'espace,tab,\",é,ç,à,etc.\n");
    int retour=0;
    while(!retour){
        printf("Entrez un nom :");
        retour=lire_long_moy(o->nom);
        if(retour==-1){
            free(o->nom);
            free(o->description);
            free(o->proprietaire);
            free(o->beneficiaire);
            free(o);
            return -1;
        }
    }
    printf("Saisir 'q' pour revenir au menu. Votre description de ressource doit etre de taille min 4 et max . Ne pas contenir : d'espace,tab,\",é,ç,à,etc.\n");
    retour=0;
    while(!retour){
        printf("Entrez une description :");
        retour=lire_long_moy(o->description);
        if(retour==-1){
            free(o->nom);
            free(o->description);
            free(o->proprietaire);
            free(o->beneficiaire);
            free(o);
            return -1;
        }
    }
    printf("Saisir '3' pour revenir au menu. Votre statut doit etre de taille min 4 et max . Ne pas contenir : é,ç,à,etc.\n");
    retour=0;
    char chaine[3];
    printf("Entrez type 1/2/3:");
    while(!lire_menu_1ou2ou3 (chaine)){
        printf("Entrez type 1/2/3:");
        if (chaine[0]=='3'){
            free(o->nom);
            free(o->description);
            free(o->proprietaire);
            free(o->beneficiaire);
            free(o);
            return -1;
        }
    }
    o->t=chaine[0]-'0';
    strcpy(o->beneficiaire,"");
    strcpy(o->proprietaire,login);
    o->en_pret=0;
    o->id=time(NULL);
    ajout_ligne_ressource(o);
    free(o->nom);
    free(o->description);
    free(o->proprietaire);
    free(o->beneficiaire);
    free(o);
    return 1;


}

void affichier_ressource(Objet o){
    printf("id :%ld, nom :%s, description :%s, type :%d, en pret :%d, proprietaire :%s, beneficiaire :%s.\n",o->id,o->nom,o->description,o->t,o->en_pret,o->proprietaire,o->beneficiaire);
}

int pret(char *login,char *login2){
    Objet o =malloc(sizeof(struct s_objet));
    o->nom=(char *)malloc(sizeof(char)*15);
    o->description=(char *)malloc(sizeof(char)*15);
    o->proprietaire=(char *)malloc(sizeof(char)*15);
    o->beneficiaire=(char *)malloc(sizeof(char)*15);
    o->id=1586441725;

    //transforme_ligne_ressource_en_sa_structure(o);
    ajouter_ligne_preter(o);
    ajouter_ligne_emprunter(o);
    free(o->proprietaire);
    free(o->beneficiaire);
    free(o->description);
    free(o->nom);
    free(o);
    return 1;
}

/* emmprunter et rendre*
attention on ne peut pas emprunter ses propres ressources
supprime benneficiaire quand rendre ? de toute façon en _pret=0*/

int emprunter(Objet o){
    o->en_pret=1;
    supprimer_et_ajouter_ligne_ressource(o);
    ajouter_ligne_preter(o);
    ajouter_ligne_emprunter(o);
    return 1;
}



int rendre(Objet o){
    modif_fichier_histo_retour_ressource(o->proprietaire,o->id);
    modif_fichier_histo_retour_ressource(o->beneficiaire,o->id);
    o->en_pret=0;
    strcpy(o->beneficiaire,"");
    supprimer_et_ajouter_ligne_ressource(o);

    return 1;
}

/*afficher les ressources et choisir laquelle emprunter*/

int recherche_par_type(){
    int type=choisir_type();
    afficher_ressource_type(type);
    return 1;
}

int choisir_type(){
    printf("Choisissez un type\n(1) Vehicules\n(2) Livres\n(3) DVD\n(4) Plantes\n");
    char chaine[3];
    while(!lire_type(chaine));
    if (chaine[0]=='1'){
        return 1;
    }
    if (chaine[0]=='2'){
        return 2;
    }
    if (chaine[0]=='3'){
        return 3;
    }
    return 4;
}

int afficher_ressource_type(int type){
    FILE *fichier=fopen("./save/ressources.json","r");
    Objet o=malloc(sizeof(struct s_objet));
    o->nom=(char *)malloc(sizeof(char)*20);
    o->description=(char *)malloc(sizeof(char)*40);
    o->proprietaire=(char *)malloc(sizeof(char)*20);
    o->beneficiaire=(char *)malloc(sizeof(char)*3);

    if (fichier!=NULL){
        char ligne[300];
        fgets(ligne,300,fichier);
        fgets(ligne,300,fichier);
        while (ligne[strlen(ligne)-2]!=']') {
            transforme_ligne_ressource_en_sa_structure(ligne,o);
            if (!o->en_pret && o->t==type){
                affichier_ressource(o);
            }

            fgets(ligne,300,fichier);

        }
    }
    free(o->nom);
    free(o->description);
    free(o->proprietaire);
    free(o->beneficiaire);
    free(o);
    fclose(fichier);
    return 1;
}

/*affiche tout le fichier resssources comme un bourrain*/
int afficher_tout(){
    FILE *fichier=fopen("./save/ressources.json","r");
    Objet o=malloc(sizeof(struct s_objet));
    o->nom=(char *)malloc(sizeof(char)*20);
    o->description=(char *)malloc(sizeof(char)*40);
    o->proprietaire=(char *)malloc(sizeof(char)*20);
    o->beneficiaire=(char *)malloc(sizeof(char)*3);

    if (fichier!=NULL){
        char ligne[300];
        fgets(ligne,300,fichier);
        fgets(ligne,300,fichier);
        while (ligne[strlen(ligne)-2]!=']') {
            transforme_ligne_ressource_en_sa_structure(ligne,o);
            affichier_ressource(o);
            fgets(ligne,300,fichier);

        }
    }
    free(o->nom);
    free(o->description);
    free(o->proprietaire);
    free(o->beneficiaire);
    free(o);
    fclose(fichier);
    return 1;
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

int recherche_id_renvoie_ligne(long int id, char *ligne_retournee){
    FILE *fichier_r=fopen("./save/ressources.json","r");
    if(fichier_r!=NULL){
        char motRech[40]="\"id\": ";
        char id_char[15];
        sprintf(id_char,"%ld",id );
        strcat(motRech,id_char);
        motRech[strlen(motRech)]=',';
        motRech[strlen(motRech)]='\0';
        char ligne[300];
        while (fgets(ligne,300,fichier_r) != NULL) {
            if (strstr(ligne, motRech) != NULL){
                strcpy(ligne_retournee,ligne);
            }
        }
        fclose(fichier_r);
        return 1;
    }
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

/*supprime la ligne avec l id fourni et la modifie avec les elements fournis et ajoute la ligne modifie a la fin*/
int supprimer_et_ajouter_ligne_ressource(Objet o){
    FILE *f_ressources=fopen("./save/ressources.json","r");
    FILE *f_temp=fopen("./save/temp_ajout_ressources.json","w");
    if (f_ressources!=NULL && f_temp!=NULL){
        char motRech[40]="\"id\": ";
        char id_char[10];
        sprintf(id_char,"%ld",o->id);
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

/* Peut modifier preter et emprunter*/
int modif_fichier_histo_retour_ressource(char *login,long int id){
    char nom_fichier[]="./save/historique/";
    strcat(nom_fichier,login);
    strcat(nom_fichier,".json");
    FILE *f_histo=fopen(nom_fichier,"r");
    FILE *f_temp=fopen("./save/historique/temp_modifie.json","w");
    if(f_histo!=NULL && f_temp!=NULL){
        struct json_object *parsed_json;
        struct json_object *rendu;
        char motRech[40]="{\"id\": ";
        char id_char[16];
        sprintf(id_char,"%ld",id );
        strcat(motRech,id_char);
        strcat(motRech,",");
        char ligne[300];
        while (fgets(ligne,300,f_histo) != NULL) {
            if (strstr(ligne, motRech) != NULL){
                parsed_json = json_tokener_parse(ligne);
                json_object_object_get_ex(parsed_json,"rendu",&rendu);
                if(json_object_get_int(rendu)==1){
                    fputs(ligne,f_temp);
                }
                else{
                    char ligne1[300];
                    int compteur=0;
                    int i=0;
                    while (compteur!=13){
                        ligne1[i]=ligne[i];
                        if(ligne[i]=='\"'){
                            compteur++;
                        }
                        i++;
                    }
                    time_t t = time(NULL);
                    char date[25];
                    strftime(date, sizeof(date), "%d-%m-%Y - %X", localtime(&t));
                    strcat(ligne1,date);
                    strcat(ligne1,"\",\"rendu\": 1,\"");
                    while (compteur!=17) {
                        if(ligne[i]=='\"'){
                            compteur++;
                        }
                        i++;
                    }
                    strcat(ligne1,&ligne[i]);
                    fputs(ligne1,f_temp);
                }
            }
            else{
                fputs(ligne,f_temp);
            }
        }
        fclose(f_histo);
        fclose(f_temp);
        remove(nom_fichier);
        rename("./save/historique/temp_modifie.json",nom_fichier);
        return 1;
    }
    return 0;
}

/*fonction a realiser
int change_nom();
int change_description();
int change_type();*/
