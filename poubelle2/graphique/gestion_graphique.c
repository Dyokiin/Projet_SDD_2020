/*#include "gestion_utilisateurs.h"
#include "gestion_ressources.h"*/
#include "gestion_graphique.h"
//#include "lecture.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

static GtkWidget *pFenetre  ;


// Permet le lancement de menu_connexion_creation_compte depuis menu_acceuil
void connexiong(){
	//menu_connexion_creation_compte(1);
	char chaine[30];
	char texte[30]="Texte haut fenetre";
	lire_texte_dialog(chaine,texte);
	//printf("%s\n",chaine );
	//printf("%s\n",texte );

}
/*
void creation_compte(){
	menu_connexion_creation_compte(2);
}
*/

/* Permet de lire du texte via une boite de dialogue nommee en paramètre */
void lire_texte_dialog(char* chaine, char* texte){

	GtkWidget *pBoite;
	gchar *sTexte;
	GtkWidget *pEntree;
	const gchar *sEntree;

	printf("Oui\n");

	if(texte != NULL){
		strcpy(sTexte, texte);
	} else {
		sTexte = "Saisie" ;
	}

	pBoite = gtk_dialog_new_with_buttons(sTexte, GTK_WINDOW(pFenetre), GTK_DIALOG_MODAL, GTK_STOCK_OK, GTK_RESPONSE_OK, NULL);
	pEntree = gtk_entry_new_with_max_length(22);
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox), pEntree, TRUE, FALSE, 5);

	gtk_widget_show_all(GTK_DIALOG(pBoite)->vbox);

	if(gtk_dialog_run(GTK_DIALOG(pBoite)) == GTK_RESPONSE_OK){
		sEntree = gtk_entry_get_text(GTK_ENTRY(pEntree));
		gtk_widget_destroy(pBoite);
	} else {
		gtk_widget_destroy(pBoite);
	}

	/*if(sEntree != NULL){
		strcpy(chaine, sEntree);
	} else {
		chaine = "" ;
	}*/

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
	g_signal_connect(G_OBJECT(pBouton[0]), "clicked", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(pBouton[1]), "clicked", G_CALLBACK(connexiong), NULL);
	/*g_signal_connect(G_OBJECT(pBouton[2]), "clicked", G_CALLBACK(creation_compte), NULL);*/

	gtk_widget_show_all(pFenetre);

}
