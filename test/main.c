#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>
#include "main.h"

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






int ressouces_pretees(char *login,char *data_debut,char *date_fin){
    char nom_fichier[]="./save/historique/";
    strcat(nom_fichier,login);
    strcat(nom_fichier,".json");
    FILE *f_histo=fopen(nom_fichier,"r");
    if (f_histo==NULL){
        perror("malloc");
        exit(EXIT_FAILURE);

    }
    struct json_object *parsed_json;
    struct json_object *id;
    struct json_object *nom;
    struct json_object *du;
    struct json_object *au;
    struct json_object *rendu;
    struct json_object *beneficiaire;

    char ligne[300];
    fgets(ligne,300,f_histo);
    int trouve=0;
    while (!trouve) {

        if (strstr(ligne,"{\"id\": 1,\"nom\": \"exemple\",\"du\": \"date debut\",\"au\": \"date de fin\",\"rendu\": 1,\"beneficiaire\": \"ici son login\"}")!=NULL){
            trouve=1;
        }
        fgets(ligne,300,f_histo);
    }
    while (ligne[strlen(ligne)-2]!=']') {

        parsed_json = json_tokener_parse(ligne);

        json_object_object_get_ex(parsed_json, "id", &id);
        json_object_object_get_ex(parsed_json, "nom", &nom);
        json_object_object_get_ex(parsed_json, "du", &du);
        json_object_object_get_ex(parsed_json, "au", &au);
        json_object_object_get_ex(parsed_json, "rendu", &rendu);
        json_object_object_get_ex(parsed_json, "beneficiaire", &beneficiaire);

        if(strcmp(data_debut,json_object_get_string(du))<=0 && strcmp(date_fin,json_object_get_string(du))>=0){
            printf("%s\n",ligne );
        }


        fgets(ligne,300,f_histo);
    }
    fclose(f_histo);
    return 1;

}

int main(int argc, char const *argv[]) {
    ressouces_pretees("bonjour","2020-04-01","2020-08-22");
    return 0;
}
