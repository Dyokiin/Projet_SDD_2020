#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "gestion_graphique.h"


int main(int argc, char *argv[]){

	gtk_init(&argc, &argv);
	
	window_init();

	menu_acceuil();

	gtk_main();

	return EXIT_SUCCESS;
}
