#include "gestion_graphique.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

static GtkWidget *pFenetre ;
static GtkWidget *pAcceuil ;

void menu_connexion(){

	GtkWidget *pBouton[2];
	GtkWidget *pLabel[2] ;
	GtkWidget *pEntryNom ;
	GtkWidget *pEntryMdp ;
	GtkWidget *pBoxV;
	GtkWidget *pBoxH[3];

	pAcceuil = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(pAcceuil), "EasyShare : connexion");
	gtk_window_set_default_size(GTK_WINDOW(pAcceuil), 400, 200);
	g_signal_connect(G_OBJECT(pAcceuil), "destroy", G_CALLBACK(retour_menu_acceuil), NULL);


	pLabel[0] = gtk_label_new("Entrez votre nom :");
	pLabel[1] = gtk_label_new("Entrez votre mdp :");

	pBouton[0] = gtk_button_new_with_label("Valider");
	pBouton[1] = gtk_button_new_with_label("Annuler");

	pBoxV = gtk_vbox_new(TRUE, 0);
	pBoxH[0] = gtk_hbox_new(TRUE, 0);
	pBoxH[1] = gtk_hbox_new(TRUE, 0);
	pBoxH[2] = gtk_hbox_new(TRUE, 0);
	gtk_container_add(GTK_CONTAINER(pAcceuil), pBoxV);

	pEntryNom = gtk_entry_new_with_max_length(22);
	pEntryMdp = gtk_entry_new_with_max_length(22);

	gtk_entry_set_visibility(GTK_ENTRY(pEntryMdp), FALSE);
	gtk_entry_set_invisible_char(GTK_ENTRY(pEntryMdp), '*');

	gtk_box_pack_start(GTK_BOX(pBoxV), pBoxH[0], TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxV), pBoxH[1], TRUE, FALSE, 0);	
	gtk_box_pack_start(GTK_BOX(pBoxV), pBoxH[2], TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxH[0]), pLabel[0], TRUE, FALSE, 0) ;
	gtk_box_pack_start(GTK_BOX(pBoxH[0]), pEntryNom, TRUE, FALSE, 0) ;
	gtk_box_pack_start(GTK_BOX(pBoxH[1]), pLabel[1], TRUE, FALSE, 0) ;
	gtk_box_pack_start(GTK_BOX(pBoxH[1]), pEntryMdp, TRUE, FALSE, 0) ;
	gtk_box_pack_start(GTK_BOX(pBoxH[2]), pBouton[0], TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxH[2]), pBouton[1], TRUE, FALSE, 0);

	g_signal_connect(G_OBJECT(pBouton[1]), "clicked", retour_menu_acceuil, NULL);

	gtk_widget_show_all(pAcceuil);


}
void menu_creation(){
}

void retour_menu_acceuil(){
	gtk_widget_destroy(pAcceuil);
}



void menu_acceuil(){

	GtkWidget *pBouton[3];
	GtkWidget *pLabel;
	GtkWidget *pBoxV ;
	GtkWidget *pBoxH ;
	GtkWidget *pLogo ;

	gchar *sUtf8 ;


	/* Creation et initialisation de la fenetre */	
	pFenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(pFenetre), "EasyShare");
	gtk_window_set_default_size(GTK_WINDOW(pFenetre), 400, 200);
	g_signal_connect(G_OBJECT(pFenetre), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	/* Creation box verticale */
	pBoxV = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(pFenetre), pBoxV);


	/* Insertion du logo EasyShare */
	pLogo = gtk_image_new_from_file("./logo_eshv1.png");
	gtk_box_pack_start(GTK_BOX(pBoxV), pLogo, FALSE, FALSE, 5);

	/* Creation, initialisation et insertion du Label EasyShare */
	pLabel = gtk_label_new(NULL);
	sUtf8 = g_locale_to_utf8("<span face=\"Sans\"><b>| EasyShare |</b></span>\n", -1, NULL, NULL, NULL) ;
	gtk_label_set_markup(GTK_LABEL(pLabel), sUtf8) ;
	g_free(sUtf8);
	gtk_box_pack_start(GTK_BOX(pBoxV), pLabel, FALSE, FALSE, 5);

	/* Creation et insertion box horizontale */
	pBoxH = gtk_hbox_new(TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxV), pBoxH, FALSE, FALSE, 5);
	
	/* Creation et placement des boutons avec du texte */
	pBouton[0] = gtk_button_new_with_label("Quitter");
	pBouton[1] = gtk_button_new_with_label("Se connecter");
	pBouton[2] = gtk_button_new_with_label("Creer un compte");

	gtk_box_pack_start(GTK_BOX(pBoxH), pBouton[1], TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxH), pBouton[2], TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxH), pBouton[0], TRUE, FALSE, 0);

	/* Association des signaux à leur bouton respectif */
	g_signal_connect(G_OBJECT(pBouton[0]), "clicked", G_CALLBACK(gtk_main_quit), NULL) ;
	g_signal_connect(G_OBJECT(pBouton[1]), "clicked", G_CALLBACK(menu_connexion), NULL);
	g_signal_connect(G_OBJECT(pBouton[2]), "clicked", G_CALLBACK(menu_creation), NULL) ;
 
	gtk_widget_show_all(pFenetre);
	


}

