#include "gestion_graphique.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include "user.h"


static GtkWidget *pFenetre;
static GtkWidget *pBoxV ;

void window_init(){
	pFenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
}

void retour_acceuil(){
	gtk_widget_destroy(pBoxV);
	menu_acceuil();
}

/* Envoie vers le menu connexion avec un argument quelconque */
void go_menu_connexion(){
	menu_connexion("Connexion");
}

/* Envoie vers le menu creation avec un argument quelconque */
void go_menu_creation(){
	menu_creation("Creation de compte");
}


/* permet l'affichage du menu d'acceuil */
void menu_acceuil(){


	/* Initialisation des différents pointeurs vers les objets présents dans la fenetre */
	GtkWidget *pBouton[3];
	GtkWidget *pLabel;
	GtkWidget *pBoxH ;
	GtkWidget *pLogo ;

	gchar *sUtf8 ;


	/* Creation et initialisation de la fenetre */	
	gtk_window_set_title(GTK_WINDOW(pFenetre), "EasyShare");
	gtk_window_set_default_size(GTK_WINDOW(pFenetre), 400, 200);
	gtk_window_set_position(GTK_WINDOW(pFenetre), GTK_WIN_POS_CENTER);
	g_signal_connect(G_OBJECT(pFenetre), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	/* Creation box verticale */
	pBoxV = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(pFenetre), pBoxV);


	/* Insertion du logo EasyShare */
	pLogo = gtk_image_new_from_file("./logo_eshv1.png");
	gtk_box_pack_start(GTK_BOX(pBoxV), pLogo, FALSE, FALSE, 5);

	/* Creation, initialisation et insertion du Label EasyShare police Sans, Gras */
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
	g_signal_connect(G_OBJECT(pBouton[1]), "clicked", G_CALLBACK(go_menu_connexion), NULL);
	g_signal_connect(G_OBJECT(pBouton[2]), "clicked", G_CALLBACK(go_menu_creation), NULL) ;
 
	/* Affichage de la fenetre acceuil et de tout ses widgets*/
	gtk_widget_show_all(pFenetre);
	


}


/* Permet l'affichage du menu d'acceuil */
void menu_connexion(char *info){
	

	gtk_widget_destroy(pBoxV);

	/*Declaration les pointeurs vers les differents objet du menu acceuil */
	GtkWidget *pBouton[2];
	GtkWidget *pLabel[3] ;
	GtkWidget *pEntryNom ;
	GtkWidget *pEntryMdp ;
	GtkWidget *pBoxH;

	/* Initialisation et creation de la fenetre du menu */
	gtk_window_set_title(GTK_WINDOW(pFenetre), "EasyShare : connexion");
	gtk_window_set_default_size(GTK_WINDOW(pFenetre), 400, 200);
	g_signal_connect(G_OBJECT(pFenetre), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	/* Initialisations des labels */
	pLabel[0] = gtk_label_new("Entrez votre nom :");
	pLabel[1] = gtk_label_new("Entrez votre mdp :");
	pLabel[2] = gtk_label_new(info);

	/* Initialisation des boutons avec labels */
	pBouton[0] = gtk_button_new_with_label("Valider");
	pBouton[1] = gtk_button_new_with_label("Annuler");

	/* Initialisation des box et des entrys */
	pBoxV = gtk_vbox_new(TRUE, 0);
	pBoxH= gtk_hbox_new(TRUE, 0);
	gtk_container_add(GTK_CONTAINER(pFenetre), pBoxV);

	pEntryNom = gtk_entry_new_with_max_length(22);
	pEntryMdp = gtk_entry_new_with_max_length(22);

	gtk_entry_set_text(GTK_ENTRY(pEntryNom), "Nom");
	gtk_entry_set_text(GTK_ENTRY(pEntryMdp), "Motdepasse");

	gtk_entry_set_visibility(GTK_ENTRY(pEntryMdp), FALSE);
	gtk_entry_set_invisible_char(GTK_ENTRY(pEntryMdp), '*');

	/*Construction de la fenetre */
	gtk_box_pack_start(GTK_BOX(pBoxV), pLabel[2], TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxV), pEntryNom, FALSE, TRUE, 0) ;
	gtk_box_pack_start(GTK_BOX(pBoxV), pEntryMdp, FALSE, TRUE, 0) ;
	gtk_box_pack_start(GTK_BOX(pBoxV), pBoxH, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxH), pBouton[0], TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxH), pBouton[1], TRUE, FALSE, 0);

	/* Liaisons des boutons a leur signal */
	g_signal_connect(G_OBJECT(pBouton[1]), "clicked", retour_acceuil, NULL);
	g_signal_connect(G_OBJECT(pBouton[0]), "clicked", G_CALLBACK(on_valider_connexion), (GtkWidget *) pBoxV);

	gtk_widget_show_all(pFenetre);
}


/* A l'appuis du bouton valider dans menu connexion, permet l'enregistrement de la saisie clavier presente dans les entry */
void on_valider_connexion(GtkWidget *pButton, gpointer data){

	/* initialisation entrys temporaires / liste chainee / char * et malloc */
	GtkWidget *pTempEntryNom ;
	GtkWidget *pTempEntryMdp ;
	GList *pList0;
	const gchar *sNom;
	const gchar *sMdp;

	char *tNom = malloc(25*sizeof(char));
	char *tMdp = malloc(25*sizeof(char));


	/* Parcour la liste chainee et affecte les entry temporaires */
	pList0 = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)data));
	pList0 = g_list_next(pList0);
	pTempEntryNom = GTK_WIDGET(pList0->data);
	pList0 = g_list_next(pList0);
	pTempEntryMdp = GTK_WIDGET(pList0->data);


	/* recopie la saisie clavier des entrys temporaire dans les const gchar* */
	sNom = gtk_entry_get_text(GTK_ENTRY(pTempEntryNom));
	sMdp = gtk_entry_get_text(GTK_ENTRY(pTempEntryMdp));
	

	/* recopie les const gchar* dans des char* classique pour utilisation */
	strcpy(tNom, sNom);
	strcpy(tMdp, sMdp);

	gtk_widget_destroy(pBoxV);
	
	

	if(test_connexion(tNom, tMdp) == 1){
		menu_principal_user();
	} else if(test_connexion(tNom, tMdp) == 2){
		menu_principal_admin();
	} else {
		menu_connexion("Vos identifiants ne correspondent pas, reesayez");
	}

	free(tNom);
	free(tMdp);
	g_list_free(pList0);
	
}

/* Permet l'affichage du menu de creation de compte */
void menu_creation(char* info){
	gtk_widget_destroy(pBoxV);

	/* Initialisation des différents pointeurs vers les objets présents dans la fenetre */
	GtkWidget *pBouton[2];
	GtkWidget *pLabel;
	GtkWidget *pEntryNom ;
	GtkWidget *pEntryMdp ;
	GtkWidget *pBoxH;

	/* Initialisation et creation de la fenetre */
	gtk_window_set_title(GTK_WINDOW(pFenetre), "EasyShare : connexion");
	gtk_window_set_default_size(GTK_WINDOW(pFenetre), 400, 200);
	g_signal_connect(G_OBJECT(pFenetre), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	/* Initialisation du Label message */
	pLabel = gtk_label_new(info);

	/* Initialisation des deux boutons */
	pBouton[0] = gtk_button_new_with_label("Valider");
	pBouton[1] = gtk_button_new_with_label("Annuler");

	/* initialisation des deux box*/
	pBoxV = gtk_vbox_new(TRUE, 0);
	pBoxH = gtk_hbox_new(TRUE, 0);
	gtk_container_add(GTK_CONTAINER(pFenetre), pBoxV);

	
	/* initialisation et parametrage des deux entry */
	pEntryNom = gtk_entry_new_with_max_length(22);
	pEntryMdp = gtk_entry_new_with_max_length(22);

	gtk_entry_set_text(GTK_ENTRY(pEntryNom), "Nom");
	gtk_entry_set_text(GTK_ENTRY(pEntryMdp), "Motdepasse");

	gtk_entry_set_visibility(GTK_ENTRY(pEntryMdp), FALSE);
	gtk_entry_set_invisible_char(GTK_ENTRY(pEntryMdp), '*');

	/* Construction de la fenetre */
	gtk_box_pack_start(GTK_BOX(pBoxV), pLabel, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxV), pEntryNom, FALSE, TRUE, 0) ;
	gtk_box_pack_start(GTK_BOX(pBoxV), pEntryMdp, FALSE, TRUE, 0) ;
	gtk_box_pack_start(GTK_BOX(pBoxV), pBoxH, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxH), pBouton[0], TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxH), pBouton[1], TRUE, FALSE, 0);


	/* Connexion signaux boutons */
	g_signal_connect(G_OBJECT(pBouton[1]), "clicked", retour_acceuil, NULL);
	g_signal_connect(G_OBJECT(pBouton[0]), "clicked", G_CALLBACK(on_valider_creation), (GtkWidget *) pBoxV);

	gtk_widget_show_all(pFenetre);

}

/* A l'appuis du bouton valider dans creation compte, permet l'enregistrement de la saisie clavier presente dans les entry */
void on_valider_creation(GtkWidget *pButton, gpointer data){

	/* initialisation entrys temporaires / liste chainee / char * et malloc */
	GtkWidget *pTempEntryNom ;
	GtkWidget *pTempEntryMdp ;
	GList *pList0;
	const gchar *sNom;
	const gchar *sMdp;

	char *tNom = malloc(25*sizeof(char));
	char *tMdp = malloc(25*sizeof(char));


	/* Parcour la liste chainee et affecte les entry temporaires */
	pList0 = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)data));
	pList0 = g_list_next(pList0);
	pTempEntryNom = GTK_WIDGET(pList0->data);
	pList0 = g_list_next(pList0);
	pTempEntryMdp = GTK_WIDGET(pList0->data);


	/* recopie la saisie clavier des entrys temporaire dans les const gchar* */
	sNom = gtk_entry_get_text(GTK_ENTRY(pTempEntryNom));
	sMdp = gtk_entry_get_text(GTK_ENTRY(pTempEntryMdp));
	

	/* recopie les const gchar* dans des char* classique pour utilisation */
	strcpy(tNom, sNom);
	strcpy(tMdp, sMdp);

	gtk_widget_destroy(pBoxV);
	
	

	if(test_creation_compte(tNom, tMdp) == 1){
		menu_principal_user();
	} else if(test_creation_compte(tNom, tMdp) == 2){
		menu_principal_admin();
	} else {
		menu_creation("Vos identifiants sont incorrects, reesayez");
	}

	free(tNom);
	free(tMdp);
	g_list_free(pList0);
	
}




/* Permet l'affichage du menu principal Adminnistrateur*/
void menu_principal_admin(){
	gtk_widget_destroy(pBoxV);

	/* Initialisation des différents pointeurs vers les objets présents dans la fenetre */
	GtkWidget *pBouton[4];
	GtkWidget *pLabel[3] ;
	GtkWidget *pBoxH[2];

	/* Creation et initialisation de la fenetre */	
	gtk_window_set_title(GTK_WINDOW(pFenetre), "EasyShare : Admin Menu principal");
	gtk_window_set_default_size(GTK_WINDOW(pFenetre), 400, 200);
	gtk_window_set_position(GTK_WINDOW(pFenetre), GTK_WIN_POS_CENTER);
	g_signal_connect(G_OBJECT(pFenetre), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	/* Creation box verticale principale */
	pBoxV = gtk_vbox_new(TRUE, 10);
	gtk_container_add(GTK_CONTAINER(pFenetre), pBoxV);

	/* Creation et initialisation des labels */
	pLabel[0] = gtk_label_new("Menu principal");
	pLabel[1] = gtk_label_new("Admin :");
	pLabel[2] = gtk_label_new(NULL); //Label a completer avec get_user

	/* Creation des autres differentes boites */
	pBoxH[0] = gtk_hbox_new(FALSE, 5);
	pBoxH[1] = gtk_hbox_new(FALSE, 5);
	
	/* Creation et initialisation des boutons */
	pBouton[0] = gtk_button_new_with_label("Liste Ressources");
	pBouton[1] = gtk_button_new_with_label("Liste Membres");
	pBouton[2] = gtk_button_new_with_label("Tickets");
	pBouton[3] = gtk_button_new_with_label("Deconnexion");

	/* Construction de la fenetre */
	gtk_box_pack_start(GTK_BOX(pBoxV), pLabel[0], FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxV), pBoxH[0], FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxV), pBoxH[1], FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxH[0]), pLabel[1], FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxH[0]), pLabel[2], FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxH[1]), pBouton[0], FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxH[1]), pBouton[1], FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxH[1]), pBouton[2], FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxH[1]), pBouton[3], FALSE, TRUE, 0);

	/* Association des boutons a leur signaux */
//	g_signal_connect(GTK_BUTTON(pBouton[0]), "clicked", G_CALLBACK(), NULL);
//	g_signal_connect(GTK_BUTTON(pBouton[1]), "clicked", G_CALLBACK(), NULL);
//	g_signal_connect(GTK_BUTTON(pBouton[2]), "clicked", G_CALLBACK(), NULL);
	g_signal_connect(GTK_BUTTON(pBouton[3]), "clicked", G_CALLBACK(retour_acceuil), NULL);

	gtk_widget_show_all(pFenetre);

}

/* Permet l'affichage du menu principal utilisateur */
void menu_principal_user(){
	gtk_widget_destroy(pBoxV);

	/* Initialisation des différents pointeurs vers les objets présents dans la fenetre */
	GtkWidget *pBouton[4];
	GtkWidget *pLabel[3] ;
	GtkWidget *pBoxH[2];

	/* Creation et initialisation de la fenetre */	
	gtk_window_set_title(GTK_WINDOW(pFenetre), "EasyShare : Menu principal");
	gtk_window_set_default_size(GTK_WINDOW(pFenetre), 400, 200);
	gtk_window_set_position(GTK_WINDOW(pFenetre), GTK_WIN_POS_CENTER);
	g_signal_connect(G_OBJECT(pFenetre), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	/* Creation box verticale principale */
	pBoxV = gtk_vbox_new(TRUE, 10);
	gtk_container_add(GTK_CONTAINER(pFenetre), pBoxV);

	/* Creation et initialisation des labels */
	pLabel[0] = gtk_label_new("Menu principal");
	pLabel[1] = gtk_label_new("Bienvenue :");
	pLabel[2] = gtk_label_new(NULL); //Label a completer avec get_user

	/* Creation des autres differentes boites */
	pBoxH[0] = gtk_hbox_new(FALSE, 5);
	pBoxH[1] = gtk_hbox_new(FALSE, 5);
	
	/* Creation et initialisation des boutons */
	pBouton[0] = gtk_button_new_with_label("Enprunter");
	pBouton[1] = gtk_button_new_with_label("Gerer mes ressources");
	pBouton[2] = gtk_button_new_with_label("Gerer mes informations personnelles");
	pBouton[3] = gtk_button_new_with_label("Deconnexion");

	/* Construction de la fenetre */
	gtk_box_pack_start(GTK_BOX(pBoxV), pLabel[0], FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxV), pBoxH[0], FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxV), pBoxH[1], FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxH[0]), pLabel[1], FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxH[0]), pLabel[2], FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxH[1]), pBouton[0], FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxH[1]), pBouton[1], FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxH[1]), pBouton[2], FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxH[1]), pBouton[3], FALSE, TRUE, 0);

	/* Association des boutons a leur signaux */
	g_signal_connect(GTK_BUTTON(pBouton[0]), "clicked", G_CALLBACK(menu_recherche), NULL);
//	g_signal_connect(GTK_BUTTON(pBouton[1]), "clicked", G_CALLBACK(), NULL);
//	g_signal_connect(GTK_BUTTON(pBouton[2]), "clicked", G_CALLBACK(), NULL);
	g_signal_connect(GTK_BUTTON(pBouton[3]), "clicked", G_CALLBACK(retour_acceuil), NULL);

	gtk_widget_show_all(pFenetre);

}


/* Permet la recherche d'objet par type, pour les utilisateurs */
void menu_recherche(){
	GtkWidget *pLabel[2];
	GtkWidget *pBouton[6];
	
	
	gtk_window_set_title(GTK_WINDOW(pFenetre), "EasyShare : rechercher un Objet");
	gtk_window_set_position(GTK_WINDOW(pFenetre), GTK_WIN_POS_CENTER);
	g_signal_connect(G_OBJECT(pFenetre), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	pBoxV = gtk_vbox_new(TRUE, 5);
	gtk_container_add(GTK_CONTAINER(pFenetre), pBoxV);

	pLabel[0] = gtk_label_new("Vous souhaitez emprunter :");
	pLabel[1] = gtk_label_new("______________");
	
	pBouton[0] = gtk_button_new_with_label("Vehicule");
	pBouton[1] = gtk_button_new_with_label("Livre");
	pBouton[2] = gtk_button_new_with_label("DVDs");
	pBouton[3] = gtk_button_new_with_label("Plante");
	pBouton[4] = gtk_button_new_with_label("Outils");
	pBouton[5] = gtk_button_new_with_label("Annuler");
	
	gtk_box_pack_start(GTK_BOX(pBoxV), pLabel[0], FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxV), pBouton[0], FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxV), pBouton[1], FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxV), pBouton[2], FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxV), pBouton[3], FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxV), pBouton[4], FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxV), pLabel[1], FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxV), pBouton[5], FALSE, TRUE, 5);
	
//	g_signal_connect(GTK_BUTTON(pBouton[0]), "clicked", G_CALLBACK(), NULL);
//	g_signal_connect(GTK_BUTTON(pBouton[1]), "clicked", G_CALLBACK(), NULL);
//	g_signal_connect(GTK_BUTTON(pBouton[2]), "clicked", G_CALLBACK(), NULL);
//	g_signal_connect(GTK_BUTTON(pBouton[3]), "clicked", G_CALLBACK(), NULL);
//	g_signal_connect(GTK_BUTTON(pBouton[4]), "clicked", G_CALLBACK(), NULL);
	g_signal_connect(GTK_BUTTON(pBouton[5]), "clicked", G_CALLBACK(menu_principal_user), NULL);
	
	
	gtk_widget_show_all(pFenetre);

}


