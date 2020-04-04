/*interaction_fichier.h */
#ifndef __INTERACTION_FICHIER_H__
#define __INTERACTION_FICHIER_H__


int ajout_ligne_ressource(int id,char *nom,char *description,int type,int en_pret,char *proprietaire,char *beneficiaire);
int supprimer_ligne_ressource(int id);
int supprimer_et_ajouter_ligne_ressource(int id,char *nom,char *description,int type,int en_pret,char *proprietaire,char *beneficiaire);
#endif
