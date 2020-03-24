#include <stdio.h>
#include <string.h>


int ecriture(char login[100],char password[100]){
    /*char ligne_a_ajouter[200]="";
    strcat(ligne_a_ajouter,login);
    strcat(ligne_a_ajouter,"    ");
    strcat(ligne_a_ajouter,password);
    strcat(ligne_a_ajouter,"\n");*/
    //printf("%s",ligne_a_ajouter );
    FILE *fichier=NULL;
    fichier=fopen("./save.txt", "w");
    if (fichier!= NULL){
        printf("YES\n");
        fseek(fichier,0, SEEK_END);
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



int main(int argc, char *argv[]) {
    char login[100]="azertyui";
    char password[100]="aqzsedrf";
    ecriture(login,password);


    //char test[]="c:\\test.txt";
    FILE *Fichier;
    char motFr[100];
    char motR[30]="coucou";
    Fichier = fopen("./save.txt", "r");
    if (!Fichier)
         printf("ERREUR: Impossible d'ouvrir le fichier: ./save.txt.\n");


    while (fgets(motFr,100,Fichier) != NULL)
    {
        if (strstr(motFr, motR) != NULL){
            printf("'%s' trouvé dans '%s'\n", motR, motFr);
        }
    }
    fclose(Fichier);



    /*fichier=fopen("./save.txt", "r");
    char ligne[255];
    fgets(ligne, 200,fichier);
    printf("%s\n",ligne );
    fclose(fichier);*/
    return 0;
}
