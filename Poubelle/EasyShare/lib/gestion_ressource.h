/* gestion_ressources.h */

#ifndef __GESTION_RESSOURCES_H__
#define __GESTION_RESSOURCES_H__

typedef struct s_objet *Objet;

void affichier_ressource(Objet o);
int recherche_id_renvoie_ligne(char *id, char *ligne_retournee);
int ajout_ligne_ressource(Objet o);
int supprimer_ligne_ressource(int id);
int supprimer_et_ajouter_ligne_ressource(Objet o);

int transforme_ligne_ressource_en_sa_structure(Objet o);
int nouvelle_ressource(char *login);

/*int change_nom();
int change_description();
int change_type();*/




#endif
