/* users.h */

#ifndef __USERS_H__
#define __USERS_H__

typedef struct s_user *User;

void afficher_user(User u);
int lire (char *chaine,int longueur);
User new_user();
int save_user(User u);
char* chiffrement(char *mdp);
int ecriture(char login[100],char password[100]);
int lecture(char login[100]);
int menu_connection();

#endif
