#include "gestion_graphique.h"
#include "ressource.h"
#include "user.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include "user.h"
#include "calendar.h"


static GtkWidget *pFenetre;
static GtkWidget *pBoxV ;
static GtkWidget *pScrollbar;
static char user_a[22];
static char type[10];

void window_init(){
	pFenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	/* Creation et initialisation de la fenetre */
	gtk_window_set_title(GTK_WINDOW(pFenetre), "EasyShare");

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

	//Initialisation et creation de la fenetre du menu
	gtk_window_set_title(GTK_WINDOW(pFenetre), "EasyShare : connexion");
	//gtk_window_set_default_size(GTK_WINDOW(pFenetre), 400, 200);
	//g_signal_connect(G_OBJECT(pFenetre), "destroy", G_CALLBACK(gtk_main_quit), NULL);

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

	//gtk_widget_destroy(pBoxV);



	if(test_connexion(tNom, tMdp) == 1){
		strcpy(user_a, sNom);
		menu_principal_user();
	} else if(test_connexion(tNom, tMdp) == 2){
		strcpy(user_a, sNom);
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
	gtk_window_set_title(GTK_WINDOW(pFenetre), "EasyShare : Creation compte");
	//gtk_window_set_default_size(GTK_WINDOW(pFenetre), 400, 200);
	//g_signal_connect(G_OBJECT(pFenetre), "destroy", G_CALLBACK(gtk_main_quit), NULL);

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

	//gtk_widget_destroy(pBoxV);



	if(test_creation_compte(tNom, tMdp) == 0){
		gtk_window_set_title(GTK_WINDOW(pFenetre), "EasyShare : Compte cree");
		retour_acceuil();
	}
	else if (test_creation_compte(tNom,tMdp)==1){
		menu_creation("Erreur Idantifiant deja existant");
	}
	else {
		menu_creation("Caractere non autorise (\",\\,/,é,ç,à,etc.)");
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
	pLabel[2] = gtk_label_new(user_a);

	/* Creation des autres differentes boites */
	pBoxH[0] = gtk_hbox_new(FALSE, 5);
	pBoxH[1] = gtk_hbox_new(FALSE, 5);

	/* Creation et initialisation des boutons */
	pBouton[0] = gtk_button_new_with_label("Gestion Ressources");
	pBouton[1] = gtk_button_new_with_label("Gestion Membres");
	pBouton[2] = gtk_button_new_with_label("Historique des echanges");
	pBouton[3] = gtk_button_new_with_label("Deconnexion");

	/* Construction de la fenetre */
	gtk_box_pack_start(GTK_BOX(pBoxV), pLabel[0], FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxV), pBoxH[0], FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxV), pBoxH[1], FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxH[0]), pLabel[1], FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxH[0]), pLabel[2], FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxH[1]), pBouton[0], FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxH[1]), pBouton[1], FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxH[1]), pBouton[2], FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxH[1]), pBouton[3], FALSE, TRUE, 5);

	/* Association des boutons a leur signaux */
	g_signal_connect(GTK_BUTTON(pBouton[0]), "clicked", G_CALLBACK(menu_ressources_admin), NULL);
	g_signal_connect(GTK_BUTTON(pBouton[1]), "clicked", G_CALLBACK(menu_membres_admin), NULL);
//	g_signal_connect(GTK_BUTTON(pBouton[2]), "clicked", G_CALLBACK( AFFICHER HISTORIQUE FULL POUR ADMIN TU PEUX LE FAIRE), NULL);
	g_signal_connect(GTK_BUTTON(pBouton[3]), "clicked", G_CALLBACK(retour_acceuil), NULL);

	gtk_widget_show_all(pFenetre);

}

void menu_ressources_admin(){
	gtk_widget_destroy(pBoxV);

	GtkWidget *pLabel;
	GtkWidget *pBouton[3];
	GtkWidget *pBoxH;

	gtk_window_set_title(GTK_WINDOW(pFenetre), "EasyShare : Admin ressources");
	gtk_window_set_default_size(GTK_WINDOW(pFenetre), 300, 400);
	g_signal_connect(G_OBJECT(pFenetre), "destroy", G_CALLBACK(gtk_main_quit), 0);

	pBoxV = gtk_vbox_new(FALSE, 5);
	pBoxH = gtk_hbox_new(FALSE, 5);

	gtk_container_add(GTK_CONTAINER(pFenetre), pBoxV);

	pLabel = gtk_label_new("Que souhaitez vous faire ?");
	pBouton[0] = gtk_button_new_with_label("consulter les ressources");
	pBouton[1] = gtk_button_new_with_label("Supprimer une ressource");
	pBouton[2] = gtk_button_new_with_label("Annuler");

	gtk_box_pack_start(GTK_BOX(pBoxV), pLabel, FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxH), pBouton[0], FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxH), pBouton[1], FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxH), pBouton[2], FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxV), pBoxH, FALSE, TRUE, 5);

//	g_signal_connect(GTK_BUTTON(pBouton[0]), "clicked", G_CALLBACK(), NULL);
//	g_signal_connect(GTK_BUTTON(pBouton[1]), "clicked", G_CALLBACK(), NULL);
	g_signal_connect(GTK_BUTTON(pBouton[2]), "clicked", G_CALLBACK(menu_principal_admin), NULL);

	gtk_widget_show_all(pFenetre);
}

void menu_membres_admin(){
	gtk_widget_destroy(pBoxV);

	GtkWidget *pLabel;
	GtkWidget *pBouton[3];
	GtkWidget *pBoxH;

	gtk_window_set_title(GTK_WINDOW(pFenetre), "EasyShare : Admin membres");
	gtk_window_set_default_size(GTK_WINDOW(pFenetre), 300, 400);
	g_signal_connect(G_OBJECT(pFenetre), "destroy", G_CALLBACK(gtk_main_quit), 0);

	pBoxV = gtk_vbox_new(FALSE, 5);
	pBoxH = gtk_hbox_new(FALSE, 5);

	gtk_container_add(GTK_CONTAINER(pFenetre), pBoxV);

	pLabel = gtk_label_new("Que souhaitez vous faire ?");
	pBouton[0] = gtk_button_new_with_label("Listes des membres");
	pBouton[1] = gtk_button_new_with_label("Bannir un membre");
	pBouton[2] = gtk_button_new_with_label("Annuler");

	gtk_box_pack_start(GTK_BOX(pBoxV), pLabel, FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxH), pBouton[0], FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxH), pBouton[1], FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxH), pBouton[2], FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxV), pBoxH, FALSE, TRUE, 5);

//	g_signal_connect(GTK_BUTTON(pBouton[0]), "clicked", G_CALLBACK(), NULL);
//	g_signal_connect(GTK_BUTTON(pBouton[1]), "clicked", G_CALLBACK(), NULL);
	g_signal_connect(GTK_BUTTON(pBouton[2]), "clicked", G_CALLBACK(menu_principal_admin), NULL);

	gtk_widget_show_all(pFenetre);
}

/* Permet l'affichage du menu principal utilisateur */
void menu_principal_user(){
	gtk_widget_destroy(pBoxV);
	//gtk_widget_destroy(pScrollbar);
	/* Initialisation des différents pointeurs vers les objets présents dans la fenetre */
	GtkWidget *pBouton[5];
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
	pLabel[2] = gtk_label_new(user_a);

	/* Creation des autres differentes boites */
	pBoxH[0] = gtk_hbox_new(FALSE, 5);
	pBoxH[1] = gtk_hbox_new(TRUE, 5);

	/* Creation et initialisation des boutons */
	pBouton[0] = gtk_button_new_with_label("Enprunter");
	pBouton[1] = gtk_button_new_with_label("Mes ressources");
	pBouton[2] = gtk_button_new_with_label("Informations personnelles");
	pBouton[3] = gtk_button_new_with_label("Mon historique");
	pBouton[4] = gtk_button_new_with_label("Deconnexion");

	/* Construction de la fenetre */
	gtk_box_pack_start(GTK_BOX(pBoxV), pLabel[0], FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxV), pBoxH[0], FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxV), pBoxH[1], FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxH[0]), pLabel[1], FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxH[0]), pLabel[2], FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxH[1]), pBouton[0], FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxH[1]), pBouton[1], FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxH[1]), pBouton[2], FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxH[1]), pBouton[3], FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxH[1]), pBouton[4], FALSE, TRUE, 5);

	/* Association des boutons a leur signaux */
	g_signal_connect(GTK_BUTTON(pBouton[0]), "clicked", G_CALLBACK(menu_recherche_chemin1), NULL);
	g_signal_connect(GTK_BUTTON(pBouton[1]), "clicked", G_CALLBACK(go_menu_ressource_boxv), NULL);
	g_signal_connect(GTK_BUTTON(pBouton[2]), "clicked", G_CALLBACK(menu_infos_perso), NULL);
	g_signal_connect(GTK_BUTTON(pBouton[3]), "clicked", G_CALLBACK(go_calendar), NULL);
	g_signal_connect(GTK_BUTTON(pBouton[4]), "clicked", G_CALLBACK(retour_acceuil), NULL);

	gtk_widget_show_all(pFenetre);

}


void go_calendar(){
	gtk_widget_destroy(pBoxV);

  	gtk_window_set_title (GTK_WINDOW (pFenetre), "Historique");
  	gtk_container_set_border_width (GTK_CONTAINER (pFenetre), 5);
  	g_signal_connect (pFenetre, "destroy", G_CALLBACK (gtk_main_quit), NULL);
  	//g_signal_connect (pFenetre, "delete-event", G_CALLBACK (gtk_false), NULL);
  	gtk_window_set_resizable (GTK_WINDOW (pFenetre), FALSE);
	create_calendar("Selectionnez date",pFenetre);

}


void menu_recherche_chemin1(){
	gtk_widget_destroy(pBoxV);
	menu_recherche();
}


/* Permet la recherche d'objet par type, pour les utilisateurs */
void menu_recherche(){
	//gtk_widget_destroy(pScrollbar);

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
	pBouton[4] = gtk_button_new_with_label("W.I.P.");
	pBouton[5] = gtk_button_new_with_label("Annuler");

	gtk_box_pack_start(GTK_BOX(pBoxV), pLabel[0], FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxV), pBouton[0], FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxV), pBouton[1], FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxV), pBouton[2], FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxV), pBouton[3], FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxV), pBouton[4], FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxV), pLabel[1], FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxV), pBouton[5], FALSE, TRUE, 5);

	g_signal_connect(GTK_BUTTON(pBouton[0]), "clicked", G_CALLBACK(ressources_vehicules), NULL);
	g_signal_connect(GTK_BUTTON(pBouton[1]), "clicked", G_CALLBACK(ressources_livres), NULL);
	g_signal_connect(GTK_BUTTON(pBouton[2]), "clicked", G_CALLBACK(ressources_dvds), NULL);
	g_signal_connect(GTK_BUTTON(pBouton[3]), "clicked", G_CALLBACK(ressources_plantes), NULL);
//	g_signal_connect(GTK_BUTTON(pBouton[4]), "clicked", G_CALLBACK(ressource_wip), NULL);
	g_signal_connect(GTK_BUTTON(pBouton[5]), "clicked", G_CALLBACK(menu_principal_user), NULL);


	gtk_widget_show_all(pFenetre);

}

void ressources_vehicules(){
	strcpy(type, "Vehicule");
	afficher_ressources();
}
void ressources_livres(){
	strcpy(type, "Livre");
	afficher_ressources();
}
void ressources_dvds(){
	strcpy(type, "DVD");
	afficher_ressources();
}
void ressources_plantes(){
	strcpy(type, "Plante");
	afficher_ressources();
}

void go_menu_ressource_boxv(){
	gtk_widget_destroy(pBoxV);
	menu_ressources();
}


void menu_ressources(){
	//gtk_widget_destroy(pBoxV);
	//gtk_widget_destroy(pScrollbar);

	GtkWidget *pLabel;
	GtkWidget *pBouton[4];
	GtkWidget *pBoxH;

	gtk_window_set_title(GTK_WINDOW(pFenetre), "EasyShare : Mes ressources");
	gtk_window_set_default_size(GTK_WINDOW(pFenetre), 300, 400);
	g_signal_connect(G_OBJECT(pFenetre), "destroy", G_CALLBACK(gtk_main_quit), 0);

	pBoxV = gtk_vbox_new(FALSE, 5);
	pBoxH = gtk_hbox_new(FALSE, 5);

	gtk_container_add(GTK_CONTAINER(pFenetre), pBoxV);

	pLabel = gtk_label_new("Que souhaitez vous faire ?");
	pBouton[0] = gtk_button_new_with_label("Ajouter une ressource");
	pBouton[1] = gtk_button_new_with_label("Supprimer une ressource");
	pBouton[2] = gtk_button_new_with_label("Annuler");
	pBouton[3] = gtk_button_new_with_label("Rendre ressource");

	gtk_box_pack_start(GTK_BOX(pBoxV), pLabel, FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxH), pBouton[0], FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxH), pBouton[1], FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxH), pBouton[3], FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxH), pBouton[2], FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxV), pBoxH, FALSE, TRUE, 5);

	g_signal_connect(GTK_BUTTON(pBouton[0]), "clicked", G_CALLBACK(go_ajouter_ressource), NULL);
	g_signal_connect(GTK_BUTTON(pBouton[1]), "clicked", G_CALLBACK(afficher_ressources_perso), NULL);
	g_signal_connect(GTK_BUTTON(pBouton[2]), "clicked", G_CALLBACK(menu_principal_user), NULL);
	g_signal_connect(GTK_BUTTON(pBouton[3]), "clicked", G_CALLBACK(afficher_ressources_emprunte), NULL);

	gtk_widget_show_all(pFenetre);
}

void afficher_ressources_emprunte(){
	gtk_widget_destroy(pBoxV);
	int nbObj;
	//printf("%s \n",type );
	nbObj = nb_ressource_empruntee(user_a);
	printf("%s %d\n",user_a,nbObj );

	if(nbObj != 0){


		GtkWidget *pBoxH;
		GtkWidget *pBouton[2];
		GtkWidget *pLabel;
		int i = 0;


		GtkWidget *pRadio[nbObj] ;

		gtk_window_set_title(GTK_WINDOW(pFenetre), "EasyShare : Rendre");
		gtk_window_set_default_size(GTK_WINDOW(pFenetre), 300, 400);
		g_signal_connect(G_OBJECT(pFenetre), "destroy", G_CALLBACK(gtk_main_quit), 0);

		pScrollbar = gtk_scrolled_window_new(NULL, NULL);
		gtk_container_add(GTK_CONTAINER(pFenetre), pScrollbar);

		pBoxV = gtk_vbox_new(FALSE, 5);
		pBoxH = gtk_hbox_new(FALSE, 5);




		pLabel = gtk_label_new("Choisissez une ressource a rendre :");
		gtk_box_pack_start(GTK_BOX(pBoxV), pLabel, FALSE, TRUE, 5);

		gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(pScrollbar), pBoxV);
		gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(pScrollbar), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);


		pBouton[0] = gtk_button_new_with_label("Retour");
		pBouton[1] = gtk_button_new_with_label("Rendre element selectione");



		char ressource[300];
		renvoyer_ressource_empruntee(user_a, i+1, ressource);
		//printf("%s\n",ressource );
		pRadio[0] = gtk_radio_button_new_with_label(NULL, ressource);

		gtk_box_pack_start(GTK_BOX(pBoxV), pRadio[0], FALSE, FALSE, 5);


		if(nbObj != 1){

			for(i = 1;i<nbObj; i++){

				char *texte = malloc(300*sizeof(char));
				renvoyer_ressource_empruntee(user_a, i+1, texte);

				pRadio[i] = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(pRadio[0]), texte);
				gtk_box_pack_start(GTK_BOX(pBoxV), pRadio[i], FALSE, FALSE, 5);
				free(texte);
			}
		}
		gtk_box_pack_start(GTK_BOX(pBoxH), pBouton[0], FALSE, FALSE, 5);
		gtk_box_pack_start(GTK_BOX(pBoxH), pBouton[1], FALSE, FALSE, 5);

		gtk_box_pack_start(GTK_BOX(pBoxV), pBoxH, FALSE, TRUE, 5);

		g_signal_connect(G_OBJECT(pBouton[0]), "clicked", G_CALLBACK(go_menu_ressource_scrollbar), NULL);
		g_signal_connect(G_OBJECT(pBouton[1]), "clicked", G_CALLBACK(on_valider_rendre), pRadio[0]);


		gtk_widget_show_all(pFenetre);


	} else {
		menu_ressources();
	}

}

void on_valider_rendre(GtkWidget *pBtn, gpointer data) {

	GSList *pList;
	//const gchar *sObjet;
	//char *tObjet = malloc(20*sizeof(char));
	int i = 0;


	pList = gtk_radio_button_get_group(GTK_RADIO_BUTTON(data));
	int a=g_slist_length(pList);

	while(pList){
		if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pList->data))){
			//sObjet = gtk_button_get_label(GTK_BUTTON(pList->data));
			pList = NULL;
		} else {
			pList = g_slist_next(pList);
			i += 1 ;
		}
	}

	//printf("%d\n",i );
	rendre_ressource(user_a, a-i);
	printf("ressource rendue\n");
	gtk_widget_destroy(pScrollbar);
	//free(tObjet);
	menu_principal_user();
}

void affichage_histo(char *date1,char *date2){


	int nbObj;
	//printf("%s \n",type );
	nbObj = nb_ressource_histo(user_a,date1,date2);
	printf("%s %d\n",user_a,nbObj );

	if(nbObj != 0){


		GtkWidget *pBoxH;
		GtkWidget *pBouton[2];
		GtkWidget *pLabel;
		int i = 0;


		GtkWidget *pRadio[nbObj] ;
		gtk_window_set_resizable (GTK_WINDOW (pFenetre), TRUE);
		gtk_window_set_title(GTK_WINDOW(pFenetre), "EasyShare : Historique");
		gtk_window_set_default_size(GTK_WINDOW(pFenetre), 300, 400);
		g_signal_connect(G_OBJECT(pFenetre), "destroy", G_CALLBACK(gtk_main_quit), 0);

		pScrollbar = gtk_scrolled_window_new(NULL, NULL);
		gtk_container_add(GTK_CONTAINER(pFenetre), pScrollbar);

		pBoxV = gtk_vbox_new(FALSE, 5);
		pBoxH = gtk_hbox_new(FALSE, 5);




		pLabel = gtk_label_new("Choisissez une ressource a rendre :");
		gtk_box_pack_start(GTK_BOX(pBoxV), pLabel, FALSE, TRUE, 5);

		gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(pScrollbar), pBoxV);
		gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(pScrollbar), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);


		pBouton[0] = gtk_button_new_with_label("Retour menu");
		//pBouton[1] = gtk_button_new_with_label("Rendre element selectione");



		char ressource[300];
		ressouces_pretees(user_a,date1,date2,i+1,ressource);
		//printf("%s\n",ressource );
		pRadio[0] = gtk_radio_button_new_with_label(NULL, ressource);

		gtk_box_pack_start(GTK_BOX(pBoxV), pRadio[0], FALSE, FALSE, 5);


		if(nbObj != 1){

			for(i = 1;i<nbObj; i++){

				char *texte = malloc(300*sizeof(char));
				ressouces_pretees(user_a,date1,date2,i+1,texte);

				pRadio[i] = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(pRadio[0]), texte);
				gtk_box_pack_start(GTK_BOX(pBoxV), pRadio[i], FALSE, FALSE, 5);
				free(texte);
			}
		}
		gtk_box_pack_start(GTK_BOX(pBoxH), pBouton[0], FALSE, FALSE, 5);
		//gtk_box_pack_start(GTK_BOX(pBoxH), pBouton[1], FALSE, FALSE, 5);

		gtk_box_pack_start(GTK_BOX(pBoxV), pBoxH, FALSE, TRUE, 5);

		g_signal_connect(G_OBJECT(pBouton[0]), "clicked", G_CALLBACK(go_menu_principal_user_scrallbar), NULL);
		//g_signal_connect(G_OBJECT(pBouton[1]), "clicked", G_CALLBACK(on_valider_rendre), pRadio[0]);


		gtk_widget_show_all(pFenetre);


	} else {
		GtkWidget *pBouton;
		GtkWidget *pLabel;




		gtk_window_set_resizable (GTK_WINDOW (pFenetre), TRUE);
		gtk_window_set_title(GTK_WINDOW(pFenetre), "EasyShare : Historique");
		gtk_window_set_default_size(GTK_WINDOW(pFenetre), 300, 400);
		gtk_window_set_position(GTK_WINDOW(pFenetre), GTK_WIN_POS_CENTER);
		g_signal_connect(G_OBJECT(pFenetre), "destroy", G_CALLBACK(gtk_main_quit), NULL);


		pBoxV = gtk_vbox_new(FALSE, 5);
		gtk_container_add(GTK_CONTAINER(pFenetre), pBoxV);

		pBouton = gtk_button_new_with_label("Retour menu");
		pLabel = gtk_label_new("Aucune ressource sur cette periode");
		gtk_box_pack_start(GTK_BOX(pBoxV), pLabel, FALSE, TRUE, 5);
		gtk_box_pack_start(GTK_BOX(pBoxV), pBouton, FALSE, TRUE, 5);


		g_signal_connect(G_OBJECT(pBouton), "clicked", G_CALLBACK(menu_principal_user), NULL);
		gtk_widget_show_all(pFenetre);
	}


}

void go_menu_principal_user_scrallbar(){

	gtk_widget_destroy(pScrollbar);
	pBoxV = gtk_vbox_new(FALSE, 5);
	gtk_container_add(GTK_CONTAINER(pFenetre), pBoxV);
	menu_principal_user();
}



void go_ajouter_ressource(){
	ajouter_ressource("Nouvelle Ressource");
}

void ajouter_ressource(char *erreur){
	gtk_widget_destroy(pBoxV);

	/* Initialisation des différents pointeurs vers les objets présents dans la fenetre */
	GtkWidget *pBouton[2];
	GtkWidget *pLabel[2];
	GtkWidget *pEntryNom ;
	GtkWidget *pEntryDescr ;
	GtkWidget *pEntryType ;



	/* Initialisation et creation de la fenetre */
	gtk_window_set_title(GTK_WINDOW(pFenetre), "EasyShare : Nouvelle ressource");
	gtk_window_set_default_size(GTK_WINDOW(pFenetre), 400, 200);
	g_signal_connect(G_OBJECT(pFenetre), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	/* Initialisation du Label message */
	pLabel[0] = gtk_label_new(erreur);
	pLabel[1] = gtk_label_new("Type de ressource ?  Vehicule / Livre / DVD / Plante");

	/* Initialisation des deux boutons */
	pBouton[0] = gtk_button_new_with_label("Valider");
	pBouton[1] = gtk_button_new_with_label("Annuler");

	/* initialisation des deux box*/
	pBoxV = gtk_vbox_new(TRUE, 0);
	gtk_container_add(GTK_CONTAINER(pFenetre), pBoxV);


	/* initialisation et parametrage des deux entry */
	pEntryNom = gtk_entry_new_with_max_length(22);
	pEntryDescr = gtk_entry_new_with_max_length(66);
	pEntryType = gtk_entry_new_with_max_length(12);

	gtk_entry_set_text(GTK_ENTRY(pEntryNom), "Nom ressource");
	gtk_entry_set_text(GTK_ENTRY(pEntryDescr), "Petite description de la ressource");
	gtk_entry_set_text(GTK_ENTRY(pEntryType), "Type");


	/* Construction de la fenetre */

	gtk_box_pack_start(GTK_BOX(pBoxV), pLabel[0], TRUE, FALSE, 5);

	gtk_box_pack_start(GTK_BOX(pBoxV), pEntryNom, FALSE, TRUE, 0) ;
	gtk_box_pack_start(GTK_BOX(pBoxV), pEntryDescr, FALSE, TRUE, 0) ;

	gtk_box_pack_start(GTK_BOX(pBoxV), pLabel[1], TRUE, FALSE, 5);

	gtk_box_pack_start(GTK_BOX(pBoxV), pEntryType, FALSE, TRUE, 5);

	gtk_box_pack_start(GTK_BOX(pBoxV), pBouton[0], FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxV), pBouton[1], FALSE, TRUE, 15);


	/* Connexion signaux boutons */
	g_signal_connect(G_OBJECT(pBouton[1]), "clicked", G_CALLBACK(go_menu_ressource_boxv), NULL);
	g_signal_connect(G_OBJECT(pBouton[0]), "clicked", G_CALLBACK(on_valider_ajout), (GtkWidget *)pBoxV);

	gtk_widget_show_all(pFenetre);

}

void on_valider_ajout(GtkWidget *pButton, gpointer data){

	/* initialisation entrys temporaires / liste chainee / char * et malloc */
	GtkWidget *pTempEntryNom ;
	GtkWidget *pTempEntryDescr ;
	GtkWidget *pTempEntryType ;
	GList *pList0;
	const gchar *sNom;
	const gchar *sDescr;
	const gchar *sType;

	char *tNom = malloc(25*sizeof(char));
	char *tDescr = malloc(68*sizeof(char));
	char *tType = malloc(12*sizeof(char));




	/* Parcour la liste chainee et affecte les entry temporaires */
	pList0 = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)data));
	pList0 = g_list_next(pList0);
	pTempEntryNom = GTK_WIDGET(pList0->data);
	pList0 = g_list_next(pList0);
	pTempEntryDescr = GTK_WIDGET(pList0->data);
	pList0 = g_list_next(pList0);
	pList0 = g_list_next(pList0);
	pTempEntryType = GTK_WIDGET(pList0->data);


	/* recopie la saisie clavier des entrys temporaire dans les const gchar* */
	sNom = gtk_entry_get_text(GTK_ENTRY(pTempEntryNom));
	sDescr = gtk_entry_get_text(GTK_ENTRY(pTempEntryDescr));
	sType = gtk_entry_get_text(GTK_ENTRY(pTempEntryType));


	/* recopie les const gchar* dans des char* classique pour utilisation */
	strcpy(tNom, sNom);
	strcpy(tDescr, sDescr);
	strcpy(tType, sType);

	gtk_widget_destroy(pBoxV);

	if(trouve_caractere_speciaux_ressource(tNom) == 0 && trouve_caractere_speciaux_ressource(tDescr) == 0 && trouve_caractere_speciaux_ressource(tType) == 0){
		if(type_atoi(tType) != 0){
			new_ressource (tNom, tDescr, user_a, type_atoi(tType));
			free(tNom);
			free(tDescr);
			g_list_free(pList0);
			printf("ressource cree\n");
			menu_principal_user();
		}
		else{
			free(tNom);
			free(tDescr);
			free(tType);
			g_list_free(pList0);
			ajouter_ressource("Mauvais Type, reessayez.");
		}

	}
	else {
		free(tNom);
		free(tDescr);
		free(tType);
		g_list_free(pList0);
		ajouter_ressource("Caracteres non autorisees, reessayez.");
	}



}

void go_menu_ressource_scrollbar(){
	gtk_widget_destroy(pScrollbar);
	menu_ressources();
}


void afficher_ressources_perso(){
	gtk_widget_destroy(pBoxV);
	int nbObj;
	//printf("%s \n",type );
	nbObj = nb_mes_ressources(user_a);
	printf("%s %d\n",user_a,nbObj );

	if(nbObj != 0){


		GtkWidget *pBoxH;
		GtkWidget *pBouton[2];
		GtkWidget *pLabel;
		int i = 0;


		GtkWidget *pRadio[nbObj] ;

		gtk_window_set_title(GTK_WINDOW(pFenetre), "EasyShare : supprime");
		gtk_window_set_default_size(GTK_WINDOW(pFenetre), 300, 400);
		g_signal_connect(G_OBJECT(pFenetre), "destroy", G_CALLBACK(gtk_main_quit), 0);

		pScrollbar = gtk_scrolled_window_new(NULL, NULL);
		gtk_container_add(GTK_CONTAINER(pFenetre), pScrollbar);

		pBoxV = gtk_vbox_new(FALSE, 5);
		pBoxH = gtk_hbox_new(FALSE, 5);




		pLabel = gtk_label_new("Choisissez une ressource a supprimer :");
		gtk_box_pack_start(GTK_BOX(pBoxV), pLabel, FALSE, TRUE, 5);

		gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(pScrollbar), pBoxV);
		gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(pScrollbar), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);


		pBouton[0] = gtk_button_new_with_label("Retour");
		pBouton[1] = gtk_button_new_with_label("Supprimer element selectione");



		char ressource[300];
		afficher_mes_ressources(user_a, ressource, i+1);
		//printf("%s\n",ressource );
		pRadio[0] = gtk_radio_button_new_with_label(NULL, ressource);

		gtk_box_pack_start(GTK_BOX(pBoxV), pRadio[0], FALSE, FALSE, 5);


		if(nbObj != 1){

			for(i = 1;i<nbObj; i++){

				char *texte = malloc(300*sizeof(char));
				afficher_mes_ressources(user_a, texte, i+1);

				pRadio[i] = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(pRadio[0]), texte);
				gtk_box_pack_start(GTK_BOX(pBoxV), pRadio[i], FALSE, FALSE, 5);
				free(texte);
			}
		}
		gtk_box_pack_start(GTK_BOX(pBoxH), pBouton[0], FALSE, FALSE, 5);
		gtk_box_pack_start(GTK_BOX(pBoxH), pBouton[1], FALSE, FALSE, 5);

		gtk_box_pack_start(GTK_BOX(pBoxV), pBoxH, FALSE, TRUE, 5);

		g_signal_connect(G_OBJECT(pBouton[0]), "clicked", G_CALLBACK(go_menu_ressource_scrollbar), NULL);
		g_signal_connect(G_OBJECT(pBouton[1]), "clicked", G_CALLBACK(on_valider_supprimer), pRadio[0]);


		gtk_widget_show_all(pFenetre);


	} else {
		menu_ressources();
	}


}


void go_menu_recherche(){

	gtk_widget_destroy(pScrollbar);

	menu_recherche();
}


void afficher_ressources(){
	gtk_widget_destroy(pBoxV);
	int nbObj;
	printf("%s \n",type );
	nbObj = nb_ressource_empruntable_type(user_a, type);
	printf("%d\n",nbObj );

	if(nbObj != 0){


		GtkWidget *pBoxH;
		GtkWidget *pBouton[2];
		GtkWidget *pLabel;
		int i = 0;


		GtkWidget *pRadio[nbObj] ;

		gtk_window_set_title(GTK_WINDOW(pFenetre), "EasyShare : Emprunter");
		gtk_window_set_default_size(GTK_WINDOW(pFenetre), 300, 400);
		g_signal_connect(G_OBJECT(pFenetre), "destroy", G_CALLBACK(gtk_main_quit), 0);

		pScrollbar = gtk_scrolled_window_new(NULL, NULL);
		gtk_container_add(GTK_CONTAINER(pFenetre), pScrollbar);

		pBoxV = gtk_vbox_new(FALSE, 5);
		pBoxH = gtk_hbox_new(FALSE, 5);




		pLabel = gtk_label_new("Choisissez une ressource a emprunter :");
		gtk_box_pack_start(GTK_BOX(pBoxV), pLabel, FALSE, TRUE, 5);

		gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(pScrollbar), pBoxV);
		gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(pScrollbar), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);


		pBouton[0] = gtk_button_new_with_label("Retour");
		pBouton[1] = gtk_button_new_with_label("Emprunter element selectione");



		char ressource[300];
		renvoyer_ressource_type(user_a, type, i+1, ressource);
		//printf("%s\n",ressource );
		pRadio[0] = gtk_radio_button_new_with_label(NULL, ressource);

		gtk_box_pack_start(GTK_BOX(pBoxV), pRadio[0], FALSE, FALSE, 5);


		if(nbObj != 1){

			for(i = 1;i<nbObj; i++){

				char *texte = malloc(300*sizeof(char));
				renvoyer_ressource_type(user_a, type, i+1, texte);

				pRadio[i] = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(pRadio[0]), texte);
				gtk_box_pack_start(GTK_BOX(pBoxV), pRadio[i], FALSE, FALSE, 5);
				free(texte);
			}
		}
		gtk_box_pack_start(GTK_BOX(pBoxH), pBouton[0], FALSE, FALSE, 5);
		gtk_box_pack_start(GTK_BOX(pBoxH), pBouton[1], FALSE, FALSE, 5);

		gtk_box_pack_start(GTK_BOX(pBoxV), pBoxH, FALSE, TRUE, 5);

		g_signal_connect(G_OBJECT(pBouton[0]), "clicked", G_CALLBACK(go_menu_recherche), NULL);
		g_signal_connect(G_OBJECT(pBouton[1]), "clicked", G_CALLBACK(on_valider_emprunter), pRadio[0]);


		gtk_widget_show_all(pFenetre);


	} else {
		menu_recherche();
	}

}

void on_valider_emprunter(GtkWidget *pBtn, gpointer data) {

	GSList *pList;
	//const gchar *sObjet;
	//char *tObjet = malloc(20*sizeof(char));
	int i = 0;


	pList = gtk_radio_button_get_group(GTK_RADIO_BUTTON(data));
	int a=g_slist_length(pList);
	while(pList){
		if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pList->data))){
			//sObjet = gtk_button_get_label(GTK_BUTTON(pList->data));
			pList = NULL;
		} else {
			pList = g_slist_next(pList);
			i += 1 ;
		}
	}

	printf("%d\n",i );
	emprunter_ressource_type(user_a, type,a-i);
	gtk_widget_destroy(pScrollbar);
	//free(tObjet);
	menu_principal_user();
}

void on_valider_supprimer(GtkWidget *pBtn, gpointer data) {


	GSList *pList;
	//const gchar *sObjet;
	//char *tObjet = malloc(20*sizeof(char));
	int i = 0;


	pList = gtk_radio_button_get_group(GTK_RADIO_BUTTON(data));
	int a=g_slist_length(pList);
	//printf("%p\n",pList->data );
	while(pList){
		if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pList->data))){
			//sObjet = gtk_button_get_label(GTK_BUTTON(pList->data));
			pList=NULL;
		} else {
			pList = g_slist_next(pList);
			i += 1 ;
		}
	}




	//printf("%d\n",i );
	//printf("valeur %d\n", i);
	if(supprimer_ressource(user_a,a-i)==0){
		printf("Ressource supprimee \n");
		gtk_widget_destroy(pScrollbar);
		menu_principal_user();

	}
	else{
		printf("ressource pretee\n");
		gtk_widget_destroy(pScrollbar);
		afficher_ressources_perso();
	}

}


void menu_infos_perso(){
	gtk_widget_destroy(pBoxV);

	GtkWidget *pLabel[3];
	GtkWidget *pBouton[2];
	GtkWidget *pBoxH[2];

	gtk_window_set_title(GTK_WINDOW(pFenetre), "EasyShare : Emprunter");
	gtk_window_set_default_size(GTK_WINDOW(pFenetre), 300, 400);
	g_signal_connect(G_OBJECT(pFenetre), "destroy", G_CALLBACK(gtk_main_quit), 0);

	pBoxV = gtk_vbox_new(TRUE, 5);
	gtk_container_add(GTK_CONTAINER(pFenetre), pBoxV);


	pLabel[0] = gtk_label_new(user_a);
	pLabel[1] = gtk_label_new("Mot de passe");
	pLabel[2] = gtk_label_new("Autre");

	pBoxH[0] = gtk_hbox_new(TRUE, 5);
	pBoxH[1] = gtk_hbox_new(TRUE, 5);


	pBouton[0] = gtk_button_new_with_label("Modifier");
	pBouton[1] = gtk_button_new_with_label("Retour");

	gtk_box_pack_start(GTK_BOX(pBoxV), pLabel[0], FALSE, TRUE,5);
	gtk_box_pack_start(GTK_BOX(pBoxH[0]), pLabel[1], FALSE, TRUE,5);
	gtk_box_pack_start(GTK_BOX(pBoxH[0]), pBouton[0], FALSE, TRUE,5);
	gtk_box_pack_start(GTK_BOX(pBoxV), pBoxH[0], FALSE, TRUE,5);
	gtk_box_pack_start(GTK_BOX(pBoxV), pLabel[2], FALSE, TRUE,5);
	gtk_box_pack_start(GTK_BOX(pBoxV), pBouton[1], FALSE, TRUE,5);

	g_signal_connect(G_OBJECT(pBouton[1]), "clicked", G_CALLBACK(menu_principal_user), NULL);
	g_signal_connect(G_OBJECT(pBouton[0]), "clicked", G_CALLBACK(go_modifier_mdp_user), NULL);

	gtk_widget_show_all(pFenetre);
}

void go_modifier_mdp_user(){
	modifier_mdp_user("Modifiez votre Mdp");
}


void modifier_mdp_user(char *erreur){
	/*gtk_widget_destroy(pBoxV);

	gtk_window_set_title(GTK_WINDOW(pFenetre), "EasyShare : Modifer MDP");
	gtk_window_set_default_size(GTK_WINDOW(pFenetre), 300, 400);
	g_signal_connect(G_OBJECT(pFenetre), "destroy", G_CALLBACK(gtk_main_quit), 0);

	GtkWidget *pEntryMdp;
	GtkWidget *pEntryVMdp;
	GtkWidget *pBouton[2];
	GtkWidget *pLabel[3];
	GtkWidget *pBoxH;

	pLabel[0] = gtk_label_new("Entrez votre Mdp");
	pLabel[1] = gtk_label_new("Confirmez votre Mdp");
	pLabel[2] = gtk_label_new(erreur);*/

	/* Initialisation des boutons avec labels  */
	/*pBouton[0] = gtk_button_new_with_label("Valider");
	pBouton[1] = gtk_button_new_with_label("Annuler");*/

	/* Initialisation des box et des entrys */
	/*pBoxV = gtk_vbox_new(TRUE, 0);
	pBoxH = gtk_hbox_new(TRUE, 0);
	gtk_container_add(GTK_CONTAINER(pFenetre), pBoxV);

	pEntryVMdp = gtk_entry_new_with_max_length(22);
	pEntryMdp = gtk_entry_new_with_max_length(22);

	gtk_entry_set_visibility(GTK_ENTRY(pEntryVMdp), FALSE);
	gtk_entry_set_invisible_char(GTK_ENTRY(pEntryVMdp), '*');
	gtk_entry_set_visibility(GTK_ENTRY(pEntryMdp), FALSE);
	gtk_entry_set_invisible_char(GTK_ENTRY(pEntryMdp), '*');

	gtk_box_pack_start(GTK_BOX(pBoxV), pLabel[2], FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxV), pLabel[0], FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxV), pEntryMdp, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxV), pLabel[1], FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxV), pEntryVMdp, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxV), pBoxH, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxH), pBouton[0], FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(pBoxH), pBouton[1], FALSE, FALSE, 5);

	g_signal_connect(G_OBJECT(pBouton[1]), "clicked", G_CALLBACK(menu_infos_perso), NULL);
	g_signal_connect(G_OBJECT(pBouton[0]), "clicked", G_CALLBACK(on_valider_modif_mdp), (GtkWidget *) pBoxV);

	gtk_widget_show_all(pFenetre);*/


	gtk_widget_destroy(pBoxV);

	/* Initialisation des différents pointeurs vers les objets présents dans la fenetre */
	GtkWidget *pBouton[2];
	GtkWidget *pLabel;
	GtkWidget *pEntryNom ;
	GtkWidget *pEntryMdp ;
	GtkWidget *pBoxH;

	/* Initialisation et creation de la fenetre */
	gtk_window_set_title(GTK_WINDOW(pFenetre), "EasyShare :Modif MDP");
	//gtk_window_set_default_size(GTK_WINDOW(pFenetre), 400, 200);
	//g_signal_connect(G_OBJECT(pFenetre), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	/* Initialisation du Label message */
	pLabel = gtk_label_new(erreur);

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

	//gtk_entry_set_text(GTK_ENTRY(pEntryNom), "Nom");
	//gtk_entry_set_text(GTK_ENTRY(pEntryMdp), "Motdepasse");

	gtk_entry_set_visibility(GTK_ENTRY(pEntryMdp), FALSE);
	gtk_entry_set_invisible_char(GTK_ENTRY(pEntryMdp), '*');
	gtk_entry_set_visibility(GTK_ENTRY(pEntryNom), FALSE);
	gtk_entry_set_invisible_char(GTK_ENTRY(pEntryNom), '*');

	/* Construction de la fenetre */
	gtk_box_pack_start(GTK_BOX(pBoxV), pLabel, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxV), pEntryNom, FALSE, TRUE, 0) ;
	gtk_box_pack_start(GTK_BOX(pBoxV), pEntryMdp, FALSE, TRUE, 0) ;
	gtk_box_pack_start(GTK_BOX(pBoxV), pBoxH, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxH), pBouton[0], TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pBoxH), pBouton[1], TRUE, FALSE, 0);


	/* Connexion signaux boutons */
	g_signal_connect(G_OBJECT(pBouton[1]), "clicked", menu_infos_perso, NULL);
	g_signal_connect(G_OBJECT(pBouton[0]), "clicked", G_CALLBACK(on_valider_modif_mdp), (GtkWidget *) pBoxV);

	gtk_widget_show_all(pFenetre);



}



void on_valider_modif_mdp(GtkWidget *pButton, gpointer data){

	/* initialisation entrys temporaires / liste chainee / char * et malloc */
	printf("testtt\n" );
	GtkWidget *pTempEntryMdp1 ;
	GtkWidget *pTempEntryMdp2 ;
	GList *pList0;
	const gchar *sMdp1;
	const gchar *sMdp2;

	char *tMdp1 = malloc(25*sizeof(char));
	char *tMdp2 = malloc(25*sizeof(char));


	/* Parcour la liste chainee et affecte les entry temporaires */
	pList0 = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)data));
	pList0 = g_list_next(pList0);
	pTempEntryMdp1 = GTK_WIDGET(pList0->data);
	pList0 = g_list_next(pList0);
	pTempEntryMdp2 = GTK_WIDGET(pList0->data);


	/* recopie la saisie clavier des entrys temporaire dans les const gchar* */
	sMdp1 = gtk_entry_get_text(GTK_ENTRY(pTempEntryMdp1));
	sMdp2 = gtk_entry_get_text(GTK_ENTRY(pTempEntryMdp2));


	/* recopie les const gchar* dans des char* classique pour utilisation */
	strcpy(tMdp1, sMdp1);
	strcpy(tMdp2, sMdp2);

	//gtk_widget_destroy(pBoxV);

	if(strcmp(tMdp1,tMdp2)!=0){
		modifier_mdp_user("Erreur mdp non identiques");
	}
	else if (test_modifier_mdp(user_a,tMdp1)==1){
		printf("mdp modifie\n");
		 menu_infos_perso();
	}
	else{
		modifier_mdp_user("Caracteres non autorises");
	}


	free(tMdp1);
	free(tMdp2);
	g_list_free(pList0);

}
