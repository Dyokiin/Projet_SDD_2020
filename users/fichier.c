#include <stdio.h>
#include <string.h>
#include "fichier.h"

/*Ecrit a la fin du fichier un identifiant et un mot de passe*/
int ecriture(){
    char login[]="rtcfrea";
    char password[]="1217626519234264774124021682371916328828231750103353992";
    FILE* stream=fopen("save.txt", "a");

    if (stream!= NULL){
        fprintf(stream," %s %s \n",login,password);
        fclose(stream);

        return 1;
    }
    else{
        return 0;
    }
}

/* recherche un Identifiant dans le fichier et renvoie la ligne(Identifiant+MDP) sur ligne* et retourne un code d'erreur ou non*/
int recherche(char *motR, char *ligne){
    FILE *Fichier;
    char motRech[30]=" ";
    strcat(motRech,motR);
    motRech[strlen(motRech)]=' ';
    motRech[strlen(motRech)]='\0';
    char ligne1[100];
    ligne1[0]='\0';
    Fichier = fopen("./save.txt", "r");
    int a=0;
    if (!Fichier){
        printf("ERREUR: Impossible d'ouvrir le fichier: ./save.txt.\n");
        a=-1; //code Erreur
    }
    while (fgets(ligne1,99,Fichier) != NULL)
    {
        if (strstr(ligne1, motRech) != NULL){
            //printf("%s\n",ligne );
            ligne[strlen(ligne1)-1]='\0';
            strcpy(ligne,ligne1);
            a=1;
        }
    }
    fclose(Fichier);
    return a;
}

/*recherche l'occurence, la presence d'un identifiant dans le fichier. Si l'identifiant exite deja ou non. */
int recherche_occ(char *motR){
    FILE *Fichier;
    char motRech[30]=" ";
    strcat(motRech,motR);
    motRech[strlen(motRech)]=' ';
    motRech[strlen(motRech)]='\0';
    char ligne[100];
    ligne[0]='\0';
    Fichier = fopen("./save.txt", "r");
    int occurence=0;
    if (!Fichier){
        printf("ERREUR: Impossible d'ouvrir le fichier: ./save.txt.\n");
        //occurence=-1; //code Erreur
    }
    while (fgets(ligne,99,Fichier) != NULL)
    {
        if (strstr(ligne, motRech) != NULL){
            occurence=1;
        }
    }
    fclose(Fichier);
    return occurence;
}
