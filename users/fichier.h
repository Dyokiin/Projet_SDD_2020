/* fichier.h */

#ifndef __FICHIER_H__
#define __FICHIER_H__

int ecriture(char *login, char *password,int statut);
int recherche(char *motR, char *ligne);
int recherche_occ(char *motR);
int modifier_ligne(char *login, char *new_password);
int modifier_statut(char *login, int statut);
int supprimer_ligne(char *login);


#endif
