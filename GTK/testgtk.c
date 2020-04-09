#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

void OnDestroy(GtkWidget *pWidget, gpointer pData);

int main(int argc, char *argv[]){

	GtkWidget *pWindow ; //Pointeur sur la fenetre
	GtkWidget *pLabel ; //Pointeur sur un label
	gchar* sUtf8;

	gtk_init(&argc, &argv) ; //intialisation de gtk

	
	pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL) ; //initialisation de pWindow
	gtk_window_set_position(GTK_WINDOW(pWindow), GTK_WIN_POS_CENTER) ;
	gtk_window_set_default_size(GTK_WINDOW(pWindow), 300, 500) ;


	pLabel = gtk_label_new(NULL); //initialisation du label

	sUtf8 = g_locale_to_utf8("<span face =\"Courier New\"><b>Partage Truc</b></span>\n", -1, NULL, NULL, NULL) ;
	gtk_label_set_markup(GTK_LABEL(pLabel), sUtf8) ;
	g_free(sUtf8);

	gtk_container_add(GTK_CONTAINER(pWindow), pLabel) ;

	g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(OnDestroy), NULL);

	gtk_widget_show_all(pWindow) ; //affichage de pWindow

	gtk_main(); //boucle infinie en attente de signal


	gtk_widget_destroy(pWindow) ; //destruction de pWindow
	return EXIT_SUCCESS ;


}

void OnDestroy(GtkWidget *pWidget, gpointer pData) {
	gtk_main_quit();
}
