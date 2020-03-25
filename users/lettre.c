#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "lettre.h"

int chiffrement(char mdp[16],char* password_chiffre){
    //char mdp[9]="azertyui";
    char motconverti[100];
    for (int i=0; i<strlen(mdp); i++) {
        /*//printf("%c\n",mdp[i] );
        if (mdp[i]<33 || mdp[i]>126){
            printf("ERREUR\n");
        }
        else{*/
        char b[2];
        sprintf(b,"%d",mdp[i]);
        strcat(motconverti,b);
        //printf("%s\n",motconverti );

    }
    //printf("mot conv =%s\n",motconverti );
    //printf("%ld\n",strlen(motconverti));
    //0 à ajouter pour former des blocs de 4
    int rajout_bloc=strlen(motconverti)%4;
    //printf("%d\n", rajout_bloc);


    while(rajout_bloc<4 && rajout_bloc!=0){
        char a[100];
        strcpy(a,motconverti);
        motconverti[0]='0';
        motconverti[1]='\0';
        strcat(motconverti,a);
        //printf("%s\n",motconverti );
        rajout_bloc++;
    }
    //printf("mot conv0=%s\n",motconverti );
    //printf("taille =%ld\n\n",strlen(motconverti) );
    /////////////////////////////////////////////////

    char bloc[5]="";
    password_chiffre[0]='\0';

    for (int compteur=0; 4*compteur<strlen(motconverti);compteur++){
        for (int i=0; i<4;i++){
            bloc[i]=motconverti[4*compteur+i];
        }
        //printf("%s\n",bloc);
        int bloc_int=atoi(bloc);
        //printf("%d\n", bloc_int);

        //cryptage bloc par 4

        int n=3565343;
        int e = 7;
        long unsigned int bloc_c = bloc_int;
        for(int i=1; i<e;i++){
            bloc_c=(bloc_c*bloc_int)%n;

        }
        char p[20];
        //printf("%ld\n",bloc_c );
        sprintf(p,"%ld",bloc_c );
        strcat(password_chiffre,p);
        //printf("%s\n",password );
    }
    //printf("%s\n",password_chiffre );
    //printf("taille %ld\n",strlen(password_chiffre) );
    return 1;
}

/*
int main(int argc, char *argv[]) {

    for (int i=33; i < 127;i++) { // de 33 à 126
        printf("%c\n",i );
    }
    //printf("%s\n",bloc);
    int p =3;
    int q =11;
    int n = p*q;
    int phin= (p-1)*(q-1);
    e=3
    d=7 //inverse de 3 modulo 20
    // clé public (33,3)  (n,e)
     chiffrement de
    c=m^e%n
    return 0;
}
*/
