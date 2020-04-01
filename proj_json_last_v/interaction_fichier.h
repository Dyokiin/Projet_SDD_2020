/*interaction_fichier.h */

#ifndef __INTERACTION_FICHIER_H__
#define __INTERACTION_FICHIER_H__

int creation_fichier_historique_utilisateur(char *login);
int ajout_ligne_ressource(int id,char *nom,char *description,int type,int en_pret,char *proprietaire,char *beneficiaire);
int ajout_ligne_utilisateur(char *login, char *password, int statut, char *nom, char *prenom, char *email);
int recherche_occurence_login(char *login);
int recherche_login_renvoie_ligne(char *login, char *ligne_retournee);
int supprimer_ligne_users(char *login);
int supprimer_ligne_ressource(int id);
int supprimer_et_ajouter_ligne_utilisateur(char *login, char *password, int statut, char *nom, char *prenom, char *email);
int supprimer_et_ajouter_ligne_ressource(int id,char *nom,char *description,int type,int en_pret,char *proprietaire,char *beneficiaire);
#endif
