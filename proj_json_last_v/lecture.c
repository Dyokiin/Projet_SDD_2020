#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LONGEUR_MOYENNE 22
#define LONGEUR_LONG 42

int lire_long_moy (char *chaine) {
    char *pointeur=NULL;
    if (fgets(chaine,LONGEUR_MOYENNE,stdin) != NULL) {
        if (strlen(chaine)==2 && chaine[0]=='q'){//code de retour pour annule
            return -1;
        }
        if (strlen(chaine)<5){
            printf("Erreur : taille trop petite. ");
            return 0;
        }
        pointeur = strchr(chaine, '\n');
        if (pointeur != NULL) {
            *pointeur = '\0';
            for (int i=0; i<strlen(chaine); i++) {
                if (chaine[i]<33 || chaine[i]>126 || chaine[i]=='"'){
                    printf("Erreur : caracteres non autorises. ");
                    return 0;
                }
            }
            return 1;
        }
        int b = 0;
        while (b != '\n' && b != EOF) {
            b = getchar();
        }
        printf("Erreur : taille trop grande. ");
    }
    return 0;
}

int lire_menu_1ou2ou3 (char *chaine) {
    char *pointeur=NULL;
    printf("Saisissez un nombre: ");
    if (fgets(chaine,3, stdin) != NULL) {
        //printf("%s\n",chaine );
        pointeur = strchr(chaine, '\n');
        if (pointeur != NULL) {
            //printf("non nul\n");
            *pointeur = '\0';
            if (chaine[0]>48 && chaine[0]<52){
                //printf("YES\n");
                return 1;
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

int lire_menu_1ou2ou3ou4 (char *chaine) {
    char *pointeur=NULL;
    printf("Saisissez un nombre: ");
    if (fgets(chaine,3, stdin) != NULL) {
        //printf("%s\n",chaine );
        pointeur = strchr(chaine, '\n');
        if (pointeur != NULL) {
            //printf("non nul\n");
            *pointeur = '\0';
            if (chaine[0]>48 && chaine[0]<53){
                //printf("YES\n");
                return 1;
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

int lire_menu_1ou2ou3ou4ou5 (char *chaine) {
    char *pointeur=NULL;
    printf("Saisissez un nombre: ");
    if (fgets(chaine,3, stdin) != NULL) {
        //printf("%s\n",chaine );
        pointeur = strchr(chaine, '\n');
        if (pointeur != NULL) {
            //printf("non nul\n");
            *pointeur = '\0';
            if (chaine[0]>48 && chaine[0]<54){
                //printf("YES\n");
                return 1;
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

int lire_type (char *chaine) {
    char *pointeur=NULL;
    printf("Entrez le numero correspondant au type: ");
    if (fgets(chaine,3, stdin) != NULL) {
        //printf("%s\n",chaine );
        pointeur = strchr(chaine, '\n');
        if (pointeur != NULL) {
            //printf("non nul\n");
            *pointeur = '\0';
            for (int i=0; i<strlen(chaine); i++) {
                //printf("%c\n",chaine[i] );
                if (chaine[i]>48 && chaine[i]<53){
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


int lire_nom_ressource(char *chaine){
    char *pointeur=NULL;
    if (fgets(chaine,LONGEUR_MOYENNE,stdin) != NULL) {
        if (strlen(chaine)==2 && chaine[0]=='q'){//code de retour pour annule
            return -1;
        }
        if (strlen(chaine)<3){
            printf("Erreur : taille trop petite. ");
            return 0;
        }
        pointeur = strchr(chaine, '\n');
        if (pointeur != NULL) {
            *pointeur = '\0';
            for (int i=0; i<strlen(chaine); i++) {
                if (chaine[i]<32 || chaine[i]>126 || chaine[i]=='"'){
                    printf("Erreur : caracteres non autorises. ");
                    return 0;
                }
            }
            return 1;
        }
        int b = 0;
        while (b != '\n' && b != EOF) {
            b = getchar();
        }
        printf("Erreur : taille trop grande. ");
    }
    return 0;

}

int lire_description(char *chaine){
    char *pointeur=NULL;
    if (fgets(chaine,LONGEUR_LONG,stdin) != NULL) {
        if (strlen(chaine)==2 && chaine[0]=='q'){//code de retour pour annule
            return -1;
        }
        pointeur = strchr(chaine, '\n');
        if (pointeur != NULL) {
            *pointeur = '\0';
            for (int i=0; i<strlen(chaine); i++) {
                if (chaine[i]=='"'){
                    printf("Erreur : caracteres non autorises (guillemet). ");
                    return 0;
                }
            }
            return 1;
        }
        int b = 0;
        while (b != '\n' && b != EOF) {
            b = getchar();
        }
        printf("Erreur : taille trop grande. ");
    }
    return 0;
}

int lire_1ou2ou3ou4ouq(char *chaine){
    char *pointeur=NULL;
    printf("Saisissez un nombre: ");
    if (fgets(chaine,3, stdin) != NULL) {
        //printf("%s\n",chaine );
        pointeur = strchr(chaine, '\n');
        if (pointeur != NULL) {
            //printf("non nul\n");
            *pointeur = '\0';
            if(chaine[0]>48 && chaine[0]<53){
                return 1;
            }
            if(chaine[0]=='q'){
                return -1;
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


int lire_nb_ressource(int *nb_retour){
    char *pointeur=NULL;
    char chaine[10];
    printf("Saisissez un nombre: ");
    if (fgets(chaine,10, stdin) != NULL) {
        //printf("%s\n",chaine );
        pointeur = strchr(chaine, '\n');
        if (pointeur != NULL) {
            //printf("non nul\n");
            *pointeur = '\0';
            if (atoi(chaine)!=0){
                *nb_retour=atoi(chaine);
                return 1;
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

