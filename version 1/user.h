/* user.h */
#ifndef __USER_H__
#define __USER_H__

typedef struct s_user *User;



int test_connexion(char *login, char *password);
int test_creation_compte(char* login, char* password);

int trouve_caractere_speciaux(char *chaine);

int save_user(char *login,char *password);
int chiffrement(char *mdp,char* password_chiffre);
int ajout_ligne_utilisateur(User u);
int recherche_occurence_login(char *login);
int creation_fichier_historique_utilisateur(char *login);

int recherche_login_renvoie_ligne(char *login, char *ligne_retournee);
int transforme_ligne_user_en_sa_structure(User u);



#endif
