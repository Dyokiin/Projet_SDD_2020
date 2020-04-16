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

void on_valider_connexion(GtkWidget *pButton, gpointer data);
void on_valider_creation(GtkWidget *pButton, gpointer data);


