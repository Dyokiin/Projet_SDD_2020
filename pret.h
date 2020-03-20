//pret echange

typedef struct s_objet *Objet;
enum type {livre, voiture, pc, outils};
enregister_un_objet(char* nom,enum type);
supprimer_un_objet(char* nom,enum type);
emprunter(char* uti1,char* ut2,Objet objet);
rendre(Objet objet);
voir_historique(char *utilisateur);
recherche(enum type);

ecrire_json(char *texte);
lire_json();
