/* users.h */

#ifndef __INTERACTION_FICHIER_H__
#define __INTERACTION_FICHIER_H__

//les 3 fonctions suivantes vont surement disparaitre
int ajout_ligne_utilisateur_et_fichier_historique(char *login,char *password);
int creation_ressource(char *nom,char *description,int type,char *login);
int creation_ressource2(char *nom,char *description,int type,char *login);

int creation_fichier_historique_utilisateur(char *login);
int ajout_ligne_ressource(int id,char *nom,char *description,int type,int en_pret,char *proprietaire,char *beneficiaire);
int ajout_ligne_utilisateur(char *login, char *password, int statut, char *nom, char *prenom, char *email);
int recherche_occurence_login(char *login);
int recherche_login_renvoie_ligne(char *login, char *ligne_retournee);
int supprimer_ligne_users(char *login);
int supprimer_ligne_ressource(char *id);

#endif
