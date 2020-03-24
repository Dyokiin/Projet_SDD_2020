//pret echange

typedef struct s_objet *Objet; //nom + type + numéro
enum type {livre, voiture, pc, outils};
int enregister_un_objet(char* nom,enum type);
int supprimer_un_objet(char* nom,enum type);
int emprunter(char* uti1,char* ut2,Objet objet);
int rendre(Objet objet);
char* voir_historique(char *utilisateur);
char* recherche(enum type);

int ecrire_json(char *texte);
int lire_json();

void menu();
