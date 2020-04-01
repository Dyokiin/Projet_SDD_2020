#include "gestion_ressources.h"
#include <stdio.h>

enum type { VEHICULE, LIVRE, DVD, PLANTE};

struct s_object{
    int id;
    char *nom;
    char *description;
    enum type t;
    int en_pret;
    char *proprietaire;
    char *beneficiaire;
}

int nouvelle_ressource(){
    
}
