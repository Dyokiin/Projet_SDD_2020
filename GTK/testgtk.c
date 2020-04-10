#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

void OnDestroy(GtkWidget *pWidget, gpointer pData);
void AddBtn(GtkWidget *pWindow, gint i);

int main(int argc, char *argv[]){



	GtkWidget *pWindow ; //Pointeur sur la fenetre
	GtkWidget *pLabel ; //Pointeur sur un label
	gchar* sUtf8 ;
	GtkWidget *pQuitBtn ; //Pointeur bouton quitter




	gtk_init(&argc, &argv) ; //intialisation de gtk



	
	pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL) ; //initialisation de pWindow
	gtk_window_set_position(GTK_WINDOW(pWindow), GTK_WIN_POS_CENTER) ;
	gtk_window_set_default_size(GTK_WINDOW(pWindow), 300, 500) ;




	pLabel = gtk_label_new(NULL); //initialisation du label
	sUtf8 = g_locale_to_utf8("<span face =\"Courier New\"><b>Partage Truc</b></span>\n", -1, NULL, NULL, NULL) ;
	gtk_label_set_markup(GTK_LABEL(pLabel), sUtf8) ;
	g_free(sUtf8);

	//gtk_container_add(GTK_CONTAINER(pWindow), pLabel) ;



	

	g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(OnDestroy), NULL);

	AddBtn(pWindow, 3);
	
	gtk_widget_show_all(pWindow) ; //affichage de pWindow




	gtk_main(); //boucle infinie en attente de signal




	gtk_widget_destroy(pWindow) ; //destruction de pWindow
	return EXIT_SUCCESS ;


}

void OnDestroy(GtkWidget *pWidget, gpointer pData) {
	gtk_main_quit();
}

void AddBtn(GtkWidget *pWindow, gint i) {
	GtkWidget *pQuitBtn;
	
	switch(i) {
		default:
		case 0:
			pQuitBtn = gtk_button_new_with_label("Quitter");
			gtk_window_set_title(GTK_WINDOW(pWindow), "Exemple 1");
			break ;
		case 1:
			pQuitBtn = gtk_button_new_with_mnemonic("_Quitter");
			gtk_window_set_title(GTK_WINDOW(pWindow), "Exemple 2");
			break ;
		case 3:
			pQuitBtn = gtk_button_new_from_stock(GTK_STOCK_QUIT) ;
			gtk_window_set_title(GTK_WINDOW(pWindow), "Exemple 3");
			break ;
	}

	g_signal_connect(G_OBJECT(pQuitBtn), "clicked", G_CALLBACK(gtk_main_quit), NULL);
	gtk_container_add(GTK_CONTAINER(pWindow), pQuitBtn) ;
}
