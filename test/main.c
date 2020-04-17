#include <stdio.h>
#include "ressource.h"

int main(int argc, char *argv[]) {
    //char login[]="bonjour";
    //new_ressource ("ici le nom","ici la description", login,4);
    //printf("%d\n", nb_mes_ressources("bonjour"));
    //char ligne_retournee[300];
    //afficher_mes_ressources("bonjour",ligne_retournee,2);
    //printf("%s\n",ligne_retournee );
    printf("%d\n",supprimer_ressource("bonjour",1) );

    return 0;
}
