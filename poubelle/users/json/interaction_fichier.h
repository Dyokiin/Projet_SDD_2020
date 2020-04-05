
int ajout_ligne_utilisateur_et_fichier_historique(char *login,char *password);
int creation_ressource(char *nom,char *description,int type,char *login);
int creation_ressource2(char *nom,char *description,int type,char *login);
int recherche_occurence_login(char *login);
int recherche_login_renvoie_ligne(char *login, char *ligne_retournee);
int supprimer_ligne_users(char *login);
int supprimer_ligne_ressource(char *id);
