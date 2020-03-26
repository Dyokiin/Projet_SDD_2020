#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


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
