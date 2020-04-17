#include "user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>


#define LONGEUR 22
#define TAILLE_MDP_CHIFFRE 100

enum statut {BASIC, ADMIN};

struct s_user {
    char *login;
    char *password;
    enum statut s;
    char *nom;
    char *prenom;
    char *email;
};

int test_modifier_mdp(char *login,char *password){
    if (trouve_caractere_speciaux(password)){
        return 0;
    }
    User u=(User)malloc(sizeof(struct s_user));
    u->login=(char *)malloc(sizeof(char)*LONGEUR);
    u->password=(char *)malloc(sizeof(char)*TAILLE_MDP_CHIFFRE);
    u->nom=(char *)malloc(sizeof(char)*LONGEUR);
    u->prenom=(char *)malloc(sizeof(char)*LONGEUR);
    u->email=(char *)malloc(sizeof(char)*LONGEUR);
    strcpy(u->login,login);
    chiffrement(password,u->password);
    supprimer_et_ajouter_ligne_utilisateur(u);
    return 1;
}



int test_connexion(char *login, char *password){
	if(recherche_occurence_login(login)){
		char mdp_chiffre[TAILLE_MDP_CHIFFRE];
		chiffrement(password,mdp_chiffre);
		User u=malloc(sizeof(struct s_user));
		u->login=malloc(sizeof(char)*LONGEUR);
		u->password=malloc(sizeof(char)*TAILLE_MDP_CHIFFRE);
		u->prenom=malloc(sizeof(char)*LONGEUR);
		u->nom=malloc(sizeof(char)*LONGEUR);
		u->email=malloc(sizeof(char)*LONGEUR);

		strcpy(u->login,login);
		transforme_ligne_user_en_sa_structure(u);


		if(strcmp(u->password,mdp_chiffre)==0){
			if(u->s==1){
				free(u->email);
				free(u->nom);
				free(u->prenom);
				free(u->login);
				free(u->password);
				free(u);
				return 2;
			}
			else{
				free(u->email);
				free(u->nom);
				free(u->prenom);
				free(u->login);
				free(u->password);
				free(u);
				return 1;

			}
		}
		free(u->email);
		free(u->nom);
		free(u->prenom);
		free(u->login);
		free(u->password);
		free(u);

	}
	return 0;
}

int test_creation_compte(char* login, char *password){
	if(recherche_occurence_login(login)){
		return 1;
	}
	if(trouve_caractere_speciaux(login) || trouve_caractere_speciaux(password)){
		return 2;
	}
	//printf("%s %s \n",login, password );
	save_user(login,password);
	return 0;
}


int trouve_caractere_speciaux(char *chaine){
	for(int i=0;i<strlen(chaine);i++){
		if (chaine[i]<33 || chaine[i]>126 || chaine[i]=='"' || chaine[i]=='\\' || chaine[i]=='/'){
			return 1;
		}
	}
	return 0;
}


/* creer un nouvelle utilisateur avec login password demande puis statut BASIC, et nom/prenom/email a renseigner plus tard*/
int save_user(char *login,char *password){
    User u=(User)malloc(sizeof(struct s_user));
    u->login=(char *)malloc(sizeof(char)*LONGEUR);
    u->password=(char *)malloc(sizeof(char)*TAILLE_MDP_CHIFFRE);
    u->nom=(char *)malloc(sizeof(char)*3);
    u->prenom=(char *)malloc(sizeof(char)*3);
    u->email=(char *)malloc(sizeof(char)*3);
    if(u==NULL || u->login==NULL || u->password==NULL || u->nom==NULL || u->prenom==NULL || u->email==NULL){
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    strcpy(u->login,login);
    chiffrement(password,u->password);
    u->s=BASIC;
    strcpy(u->nom,"");
    strcpy(u->prenom,"");
    strcpy(u->email,"");

    ajout_ligne_utilisateur(u);
    creation_fichier_historique_utilisateur(u->login);
    free(u->login);
    free(u->password);
    free(u->prenom);
    free(u->nom);
    free(u->email);
    free(u);
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
renvoie 1 s'il existe deja, 0 s'il  n''existe pas */
int recherche_occurence_login(char *login){
    FILE *fichier_users=fopen("./save/users.json","r");

    int occurence=0;
    if (!fichier_users){
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
