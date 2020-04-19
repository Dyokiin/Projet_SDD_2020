/* gestion_ressources.h */

#ifndef __RESSOURCES_H__
#define __RESSOURCES_H__

typedef struct s_objet *Objet;

int type_atoi(char *type);
int nb_ressource_empruntable_type(char *login,char *type);
int nb_ressource_perso(char *login);
int renvoyer_ressource_type(char *login,char *type, int numero, char *ligne_retournee);
int renvoyer_ressource_perso(char *login, int numero, char *ligne_retournee);
int emprunter_ressource_type(char *login,char *type,int numero);
int emprunter(Objet o);
int supprimer_et_ajouter_ligne_ressource(Objet o);
int ajouter_ligne_emprunter(Objet o);
int ajouter_ligne_preter(Objet o);
int transforme_ligne_ressource_en_sa_structure(char *ligne,Objet o);

int ajout_ligne_ressource(Objet o);
int new_ressource (char *nom,char * description, char *login,int type);
int trouve_caractere_speciaux_ressource(char *chaine);

int nb_mes_ressources(char *login);
int afficher_mes_ressources(char *login, char *ligne_retournee,int numero);

int supprimer_ressource(char *login,int numero);
int supprimer_ligne_ressource(int id);
int test_modifier_mdp(char *login,char *password);

#endif
