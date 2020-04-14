#include "gestion_utilisateurs.h"
#include "gestion_ressources.h"
#include "gestion_graphique.h"
#include "lecture.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

static GtkWidget *pFenetre  ;

/* Permet le lancement de menu_connexion_creation_compte depuis menu_acceuil */
void connexiong(){
	menu_connexion_creation_compte(1);
}

void creation_compte(){
	menu_connexion_creation_compte(2);
}


/* Boite de dialogue permettant de renseigner Nom et Mot de passe A COMPLETER */
void get_mdp(char* chaine){
	int ok = 1;
	while(ok == 1){
		GtkWidget* pBoite;
		GtkWidget* pErreur[4];
		GtkWidget* pMdp;
		const gchar* sMdp;
		int rep = 0 ;
		int erreur = 3;

		gchar *sUtf8 ;
	
		pBoite = gtk_dialog_new_with_buttons("Saisie mdp", GTK_WINDOW(pFenetre), GTK_DIALOG_MODAL, GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
		pErreur[0] = gtk_label_new("Taille trop petite.");
		pErreur[1] = gtk_label_new("Taille trop grande.");
		pErreur[2] = gtk_label_new(NULL);
		pErreur[3] = gtk_label_new(NULL);
		sUtf8 = g_locale_to_utf8("caractère non autorisé", -1, NULL, NULL, NULL);
		gtk_label_set_markup(GTK_LABEL(pErreur[2]), sUtf8);
		g_free(sUtf8);


		pMdp = gtk_entry_new_with_max_length(21);
		gtk_entry_set_text(GTK_ENTRY(pMdp), "Saisissez votre mdp");

		gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox), pErreur[erreur], TRUE, FALSE, 0);	
		gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox), pMdp, TRUE, FALSE, 0);
	
		gtk_widget_show_all(GTK_DIALOG(pBoite)->vbox);
	
		switch (gtk_dialog_run(GTK_DIALOG(pBoite))) {
			case GTK_RESPONSE_OK:
				sMdp = gtk_entry_get_text(GTK_ENTRY(pMdp));
				rep = 1;
				break;
			case GTK_RESPONSE_CANCEL:
				break;
			case GTK_RESPONSE_NONE:
				break;
			default :
				break;
		}
	
		if (rep==1){
			strcpy(chaine, sMdp);
		}

		char *pointeur=NULL;
    		if (chaine != NULL) {
	        	if (strlen(chaine)<5){
       				erreur = 0;
       			}
        		pointeur = strchr(chaine, '\n');
        		if (pointeur != NULL) {
            			*pointeur = '\0';
            			for (int i=0; i<strlen(chaine); i++) {
                			if (chaine[i]<33 || chaine[i]>126 || chaine[i]=='"'){
                	    		erreur = 3;
                			}
            			}

        		}
    		} else {
			ok = 0;
		}
		gtk_widget_destroy(pBoite);
	}
	
	printf("caca2");
	
}

void get_nom(char* chaine){
	int erreur = 2;
	GtkWidget* pBoite;

		GtkWidget* pErreur[4];
		GtkWidget* pNom;
		const gchar* sNom;
		int rep = 0 ;


		gchar *sUtf8 ;
	
		pBoite = gtk_dialog_new_with_buttons("Saisie nom", GTK_WINDOW(pFenetre), GTK_DIALOG_MODAL, GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
		pErreur[0] = gtk_label_new("Taille trop petite.");
		pErreur[1] = gtk_label_new("Taille trop grande.");
		pErreur[2] = gtk_label_new("Nom");
		pErreur[3] = gtk_label_new(NULL);
		sUtf8 = g_locale_to_utf8("caractère non autorisé", -1, NULL, NULL, NULL);
		gtk_label_set_markup(GTK_LABEL(pErreur[3]), sUtf8);
		g_free(sUtf8);


		pNom = gtk_entry_new_with_max_length(21);

		gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox), pErreur[erreur], TRUE, FALSE, 0);	
		gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox), pNom, TRUE, FALSE, 0);
	
		gtk_widget_show_all(GTK_DIALOG(pBoite)->vbox);
	
		switch (gtk_dialog_run(GTK_DIALOG(pBoite))) {
			case GTK_RESPONSE_OK:
				sNom = gtk_entry_get_text(GTK_ENTRY(pNom));
				rep = 1;

				break;
			case GTK_RESPONSE_CANCEL:


			case GTK_RESPONSE_NONE:


			default :
				gtk_widget_destroy(pBoite);
				break;
		}
		
		gtk_widget_destroy(pBoite);
	
		if (rep==1){
			strcpy(chaine, sNom);
			printf("%s\n", chaine);
		}
	



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
	g_signal_connect(G_OBJECT(pBouton[2]), "clicked", G_CALLBACK(creation_compte), NULL);

	gtk_widget_show_all(pFenetre);

}

