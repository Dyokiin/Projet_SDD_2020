#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "gestion_utilisateurs.h"
#include "gestion_ressources.h"
#include "bouttons.h"

int main(int argc, char *argv[]){

	GtkWidget *pFenetre ;
	GtkWidget *pBouttons;
	GtkWidget *pBoxV ;
	GtkWidget *pBoxH ;

	gtk_init(&argc, &argv);
	
	pFenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(pFenetre), "EasyShare");
	gtk_window_set_default_size(GTK_WINDOW(pFenetre), 400, 200);
	g_signal_connect(G_OBJECT(pFenetre), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	

	
	gtk_main();

	return EXIT_SUCCESS;
}
