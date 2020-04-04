#include <stdio.h>
#include <string.h>
#define LONGEUR_MOYENNE 10

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
    printf("Entrez 1 ou 2 ou 3 :");
    if (fgets(chaine,3, stdin) != NULL) {
        //printf("%s\n",chaine );
        pointeur = strchr(chaine, '\n');
        if (pointeur != NULL) {
            //printf("non nul\n");
            *pointeur = '\0';
            for (int i=0; i<strlen(chaine); i++) {
                //printf("%c\n",chaine[i] );
                if (chaine[i]>48 && chaine[i]<52){
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
