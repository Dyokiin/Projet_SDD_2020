/*permet la gestion du fichier de stockage login password : ecriture,
lecture, recherche */
#include "fichier.h"
#include <stdio.h>
#include <string.h>


/*Ecrit a la fin du fichier un identifiant et un mot de passe*/
int ecriture(char *login,char *password,int statut){
    FILE* stream=fopen(".save", "a");
    if (stream!= NULL){
        fprintf(stream,"%d %s %s\n",statut,login,password);
        fclose(stream);
        return 1;
    }
    else{
        return 0;
    }
}

/* recherche un Identifiant dans le fichier et renvoie la ligne(Identifiant+MDP) sur ligne* et retourne un code d'erreur ou non*/
int recherche(char *motR, char *ligne){
    FILE *Fichier= fopen(".save", "r");
    char motRech[100]=" ";
    strcat(motRech,motR);
    motRech[strlen(motRech)]=' ';
    motRech[strlen(motRech)]='\0';
    char ligne1[100]="";
    int code_retour=0;
    if (!Fichier){
        printf("ERREUR: Impossible d'ouvrir le fichier: ./save.txt.\n");
        code_retour=-1; //code Erreur
    }
    else{
        while (fgets(ligne1,99,Fichier) != NULL)
        {
            if (strstr(ligne1, motRech) != NULL){
                //printf("%s\n",ligne );
                ligne[strlen(ligne1)-1]='\0';
                strcpy(ligne,ligne1);
                code_retour=1;
            }
        }
        fclose(Fichier);
    }
    return code_retour;
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
    Fichier = fopen(".save", "r");
    int occurence=0;
    if (!Fichier){
        printf("ERREUR: Impossible d'ouvrir le fichier ou fichier inexistant.\n");
        //occurence=-1; //code Erreur
    }
    else{
        while (fgets(ligne,99,Fichier) != NULL)
        {
            if (strstr(ligne, motRech) != NULL){
                occurence=1;
            }
        }
        fclose(Fichier);
    }
    return occurence;
}

int modifier_ligne(char *login, char *new_password){
    FILE *fichier=fopen(".save","r");
    FILE *temp=fopen(".temp","w");
    char motRech[100]=" ";
    strcat(motRech,login);
    motRech[strlen(motRech)]=' ';
    motRech[strlen(motRech)]='\0';
    if (!fichier || !temp){
        printf("Erreur\n");
        return 0;
    }
    else{
        char ligne[100];
        while(fgets(ligne,100,fichier)!=NULL){
            if(strstr(ligne,motRech)!=NULL){
                fprintf(temp,"%c %s %s\n",ligne[0],login,new_password);
            }
            else{
                fputs(ligne,temp);
            }
        }

    }
    fclose(temp);
    fclose(fichier);
    remove(".save");
    rename(".temp",".save");
    return 1;
}
int modifier_statut(char *login, int statut){
    FILE *fichier=fopen(".save","r");
    FILE *temp=fopen(".temp","w");
    char motRech[100]=" ";
    strcat(motRech,login);
    motRech[strlen(motRech)]=' ';
    motRech[strlen(motRech)]='\0';
    if (!fichier || !temp){
        printf("Erreur\n");
        return 0;
    }
    else{
        char ligne[100];
        while(fgets(ligne,100,fichier)!=NULL){
            if(strstr(ligne,motRech)!=NULL){
                fprintf(temp,"%d%s",statut,&ligne[1]);
            }
            else{
                fputs(ligne,temp);
            }
        }

    }
    fclose(temp);
    fclose(fichier);
    remove(".save");
    rename(".temp",".save");
    return 1;
}






int supprimer_ligne(char *login){
    FILE *fichier=fopen(".save","r");
    FILE *temp=fopen(".temp","w");
    char motRech[100]=" ";
    strcat(motRech,login);
    motRech[strlen(motRech)]=' ';
    motRech[strlen(motRech)]='\0';
    if (!fichier || !temp){
        printf("Erreur\n");
        return 0;
    }
    else{
        char ligne[100];
        while(fgets(ligne,100,fichier)!=NULL){
            if(!(strstr(ligne,motRech)!=NULL)){
                fputs(ligne,temp);
            }
        }

    }
    fclose(temp);
    fclose(fichier);
    remove(".save");
    rename(".temp",".save");
    return 1;

}
