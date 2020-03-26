#ifndef __USERS_H__
#define __USERS_H__

typedef struct s_user *User;

int new_user();
int lire (char *chaine);
int save_user(User u);
int connexion();
int lire_menu_1ou2 (char *chaine);
int menu_connexion();

#endif
