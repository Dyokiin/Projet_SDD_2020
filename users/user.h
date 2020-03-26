#ifndef __USER_H__
#define __USER_H__

typedef struct s_user *User;

int new_user();
int lire (char *chaine);
int save_user(User u);
int connexion(User u);
int lire_menu_1ou2ou3 (char *chaine);
int menu_connexion();
int menu_utilisateur(User u);
int menu_admin(User u);
int modifier_password(char *login);

#endif
