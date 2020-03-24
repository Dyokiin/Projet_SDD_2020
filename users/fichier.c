#include <stdio.h>
#include <string.h>


int ecriture(char login[100],char password[100]){
    /*char ligne_a_ajouter[200]="";
    strcat(ligne_a_ajouter,login);
    strcat(ligne_a_ajouter,"    ");
    strcat(ligne_a_ajouter,password);
    strcat(ligne_a_ajouter,"\n");
    //printf("%s",ligne_a_ajouter );*/
    FILE *fichier=NULL;
    fichier=fopen("./save.txt", "a");
    if (fichier!= NULL){
        printf("YES\n");
        //fputs(ligne_a_ajouter,fichier);
        fprintf(fichier,"%s    %s\n",login,password);
        fclose(fichier);
        return 1;
    }
    else{
        printf("Ecriture impossible : pas acces fichier\n");
        return 0;
    }
}

int recherche(char motR[30], char ligne[100]){
    FILE *Fichier;
    ligne[0]='\0';
    Fichier = fopen("./save.txt", "r");
    int occurence=0;
    if (!Fichier){
        printf("ERREUR: Impossible d'ouvrir le fichier: ./save.txt.\n");
        occurence=-1; //code Erreur
    }
    while (fgets(ligne,99,Fichier) != NULL)
    {
        if (strstr(ligne, motR) != NULL){
            occurence=1;
        }
    }
    fclose(Fichier);
    ligne[strlen(ligne)-1]='\0';
    return occurence;
}


int main(int argc, char *argv[]) {
    char login[100]="azertyui";
    char password[100]="aqzsedrf";
    char ligne[100];
    ecriture(login,password);
    printf("%d\n",recherche(login,ligne));
    printf("%s\n",ligne );


    return 0;
}
