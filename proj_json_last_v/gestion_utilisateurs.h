/* gestion_utilisateur.h */
#ifndef __GESTION_UTILISATEUR_H__
#define __GESTION_UTILISATEUR_H__

typedef struct s_user *User;

void afficher_user(User u);
int recherche_occurence_login(char *login);
int recherche_login_renvoie_ligne(char *login, char *ligne_retournee);
int ajout_ligne_utilisateur(User u);
int supprimer_ligne_users(char *login);
int supprimer_et_ajouter_ligne_utilisateur(User u);

int chiffrement(char *mdp,char* password_chiffre);
int transforme_ligne_user_en_sa_structure(User u);
int new_user();
int creation_fichier_historique_utilisateur(char *login);
int menu_connexion_creation_compte();
int connexion(User u);

int change_password(User u);
int change_statut(User u);
int change_nom(User u);
int change_prenom(User u);
int change_email(User u);


int menu_utilisateur(User u);
int menu_admin(User u);


#endif
