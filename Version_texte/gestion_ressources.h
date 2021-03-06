/* gestion_ressources.h */

#ifndef __GESTION_RESSOURCES_H__
#define __GESTION_RESSOURCES_H__

typedef struct s_objet *Objet;

void affichier_ressource(Objet o);
int recherche_id_renvoie_ligne(long int id, char *ligne_retournee);
int ajout_ligne_ressource(Objet o);
int supprimer_ligne_ressource(int id);
int supprimer_et_ajouter_ligne_ressource(Objet o);

int transforme_ligne_ressource_en_sa_structure(char *ligne,Objet o);
int nouvelle_ressource(char *login);


int ajouter_ligne_preter(Objet o);
int ajouter_ligne_emprunter( Objet o);
int modif_fichier_histo_retour_ressource(char *login,long int id);


int pret(char *login,char *login2);

int rendre(Objet o);
int emprunter(Objet o);

int rendre_ressource(char *login,int nb);
int emprunter_ressource_type(int type,char *login,int nb);

int choisir_type();

int afficher_ressource_type(int type,char *login);
int afficher_tout();
int afficher_ressources_pretees(char *login);
int afficher_ressources_empruntees(char *login);
int afficher_ressources_empruntees_compteur(char *login,int *nb);
int afficher_ressource_type_nb(int type,char *login,int *nb);


int recherche_par_type(char *login,int *type);
/*int change_nom();
int change_description();
int change_type();*/




#endif

