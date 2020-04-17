#include <gtk/gtk.h>

void window_init();

void retour_acceuil();
void go_menu_connexion();
void go_menu_creation();
void menu_connexion();
void menu_creation();
void menu_acceuil();
void menu_principal_user();
void menu_principal_admin();
void menu_recherche();
void afficher_ressources(char * type);
void menu_infos_perso();
void menu_ressources();
void afficher_ressources_perso();
void menu_infos_perso();

void menu_ressources_admin();
void menu_membres_admin();

void ressources_vehicules();
void ressources_dvds();
void ressources_plantes();
void ressources_livres();

void on_valider_connexion(GtkWidget *pButton, gpointer data);
void on_valider_creation(GtkWidget *pButton, gpointer data);
void on_valider_emprunter(GtkWidget *pButton, gpointer data);
void on_valider_supprimer(GtkWidget *pButton, gpointer data);


