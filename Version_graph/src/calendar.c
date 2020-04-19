/*
 * Copyright (C) 1998 Cesar Miquel, Shawn T. Amundson, Mattias Grönlund
 * Copyright (C) 2000 Tony Gale
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <stdio.h>
#include <string.h>
#include "../lib/gestion_graphique.h"
#include "../lib/calendar.h"
#include <gtk/gtk.h>

#define DEF_PAD 10
#define DEF_PAD_SMALL 5

#define TM_YEAR_BASE 1900

typedef struct _CalendarData {
  GtkWidget *flag_checkboxes[5];
  gboolean  settings[5];
  GtkWidget *font_dialog;
  GtkWidget *window;

  GtkWidget *last_sig;
  GtkWidget *month;
} CalendarData;

enum {
  calendar_show_header,
  calendar_show_days,
  calendar_month_change,
  calendar_show_week,
  calendar_monday_first
};

/*
 * GtkCalendar
 */






static void calendar_date_to_string( CalendarData *data, char *buffer, gint buff_len )
{
  GDate date;
  guint year, month, day;

  gtk_calendar_get_date (GTK_CALENDAR (data->window), &year, &month, &day);
  g_date_set_dmy (&date, day, month + 1, year);
  g_date_strftime (buffer, buff_len - 1, "%Y-%m-%d", &date);

}



void verifie_selection(GtkWidget *button, GSList *premier){
    GtkWidget *signal=(GtkWidget*) g_slist_nth_data(premier, 0);
    GtkWidget *signal2=(GtkWidget*) g_slist_nth_data(premier, 1);
    const gchar *text;
    const gchar *text2;
    text=gtk_label_get_text(GTK_LABEL (signal));
    text2=gtk_label_get_text(GTK_LABEL (signal2));



    if (strcmp(text,"")==0 || strcmp(text2,"")==0){
        //printf("vide\n");

        gtk_widget_destroy(g_slist_nth_data(premier,2));
        create_calendar("Erreur. Selection date",g_slist_nth_data(premier,3));

    }


    else{

        if(strcmp(text,text2)>=0){
            gtk_widget_destroy(g_slist_nth_data(premier,2));
            create_calendar("Aie Aie Aie les dates",g_slist_nth_data(premier,3));
            g_slist_free(premier);
        }

        else{
            printf("signal1:%s!   | signal2:%s\n", text,text2);
            char date1[20];
            char date2[20];
            strcpy(date1,text);
            strcpy(date2,text2);
            gtk_widget_destroy(g_slist_nth_data(premier,2));
            affichage_histo(date1,date2);
            //gtk_widget_destroy(g_slist_nth_data(premier,3));
            g_slist_free(premier);

        }



    }





}





static void calendar_set_signal_strings( char *sig_str, CalendarData *data )
{
  //const gchar *prev_sig;



  //prev_sig = gtk_label_get_text (GTK_LABEL (data->last_sig));

  gtk_label_set_text (GTK_LABEL (data->last_sig), sig_str);
}

static void calendar_month_changed( GtkWidget    *widget,CalendarData *data )
{
  char buffer[256] = "month_changed: ";

  calendar_date_to_string (data, buffer + 15, 256 - 15);
  calendar_set_signal_strings (buffer, data);
}

static void calendar_day_selected( GtkWidget    *widget, CalendarData *data )
{
  char buffer[256] = "";

  calendar_date_to_string (data, buffer , 256);
  calendar_set_signal_strings (buffer, data);
}



static void calendar_prev_month( GtkWidget    *widget, CalendarData *data )
{
  char buffer[256] = "prev_month: ";

  calendar_date_to_string (data, buffer + 12, 256 - 12);
  calendar_set_signal_strings (buffer, data);
}

static void calendar_next_month( GtkWidget    *widget,  CalendarData *data )
{
  char buffer[256] = "next_month: ";

  calendar_date_to_string (data, buffer + 12, 256 - 12);
  calendar_set_signal_strings (buffer, data);
}

static void calendar_prev_year( GtkWidget    *widget,  CalendarData *data )
{
  char buffer[256] = "prev_year: ";

  calendar_date_to_string (data, buffer + 11, 256 - 11);
  calendar_set_signal_strings (buffer, data);
}

static void calendar_next_year( GtkWidget    *widget, CalendarData *data )
{
  char buffer[256] = "next_year: ";

  calendar_date_to_string (data, buffer + 11, 256 - 11);
  calendar_set_signal_strings (buffer, data);
}


static void calendar_set_flags( CalendarData *calendar )
{
  gint i;
  gint options = 0;
  for (i = 0;i < 5; i++)
    if (calendar->settings[i])
      {
	options = options + (1 << i);
      }
  if (calendar->window)
    gtk_calendar_display_options (GTK_CALENDAR (calendar->window), options);
}
/*
static void calendar_toggle_flag( GtkWidget    *toggle, CalendarData *calendar)
{
  gint i;
  gint j;
  j = 0;
  for (i = 0; i < 5; i++)
    if (calendar->flag_checkboxes[i] == toggle)
      j = i;

  calendar->settings[j] = !calendar->settings[j];
  calendar_set_flags (calendar);

}

static void calendar_font_selection_ok( GtkWidget    *button, CalendarData *calendar )
{
  GtkRcStyle *style;
  char *font_name;

  if (calendar->window)
    {
      font_name = gtk_font_selection_dialog_get_font_name (GTK_FONT_SELECTION_DIALOG (calendar->font_dialog));
      if (font_name)
	{
	  style = gtk_rc_style_new ();
	  pango_font_description_free (style->font_desc);
	  style->font_desc = pango_font_description_from_string (font_name);
	  gtk_widget_modify_style (calendar->window, style);
	  g_free (font_name);
	}
    }

  gtk_widget_destroy (calendar->font_dialog);
}

static void calendar_select_font( GtkWidget    *button,CalendarData *calendar )
{
  GtkWidget *window;

  if (!calendar->font_dialog) {
    window = gtk_font_selection_dialog_new ("Font Selection Dialog");
    g_return_if_fail (GTK_IS_FONT_SELECTION_DIALOG (window));
    calendar->font_dialog = window;

    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_MOUSE);

    g_signal_connect (window, "destroy", G_CALLBACK (gtk_widget_destroyed),&calendar->font_dialog);

    g_signal_connect (GTK_FONT_SELECTION_DIALOG (window)->ok_button,"clicked", G_CALLBACK (calendar_font_selection_ok), calendar);
    g_signal_connect_swapped (GTK_FONT_SELECTION_DIALOG (window)->cancel_button,"clicked", G_CALLBACK (gtk_widget_destroy),calendar->font_dialog);
  }
  window = calendar->font_dialog;
  if (!GTK_WIDGET_VISIBLE (window))
    gtk_widget_show (window);
  else
    gtk_widget_destroy (window);

}
*/
void create_calendar( char *erreur,GtkWidget *window ) {

  GtkWidget *vbox, *vbox2;
  GtkWidget *hbox;
  GtkWidget *hbbox;
  GtkWidget *calendar;
  GtkWidget *calendar2;
//  GtkWidget *toggle;
  GtkWidget *button, *button2;
  GtkWidget *frame;
  GtkWidget *separator;
  GtkWidget *label;
  GtkWidget *bbox;
  GtkWidget *labelErreur;
  static CalendarData calendar_data;
  static CalendarData calendar2_data;
  gint i;

/*  struct {
    char *label;
  } flags[] =
    {
      { "Show Heading" },
      { "Show Day Names" },
      { "No Month Change" },
      { "Show Week Numbers" },
      { "Week Start Monday" }
    };
*/

  calendar_data.window = NULL;
  calendar2_data.window=NULL;
  calendar_data.font_dialog = NULL;
  calendar2_data.font_dialog=NULL;

  calendar_data.settings[0] = 1;
  calendar2_data.settings[0]=1;

  for (i = 1; i < 5; i++) {
    calendar_data.settings[i] = 0;
    calendar2_data.settings[i]=0;
  }



  vbox = gtk_vbox_new (FALSE, DEF_PAD);
  gtk_container_add (GTK_CONTAINER (window), vbox);
  labelErreur=gtk_label_new(erreur);
  gtk_box_pack_start(GTK_BOX(vbox),labelErreur,TRUE,FALSE,DEF_PAD_SMALL);

  /*
   * The top part of the window, Calendar, flags and fontsel.
   */

  hbox = gtk_hbox_new (FALSE, DEF_PAD);
  gtk_box_pack_start (GTK_BOX (vbox), hbox, TRUE, TRUE, DEF_PAD);
  hbbox = gtk_hbutton_box_new ();
  gtk_box_pack_start (GTK_BOX (hbox), hbbox, FALSE, FALSE, DEF_PAD);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (hbbox), GTK_BUTTONBOX_SPREAD);
  gtk_box_set_spacing (GTK_BOX (hbbox), 5);

  /* Calendar widget */
  frame = gtk_frame_new ("Calendar Debut");
  gtk_box_pack_start(GTK_BOX (hbbox), frame, FALSE, TRUE, DEF_PAD);
  calendar=gtk_calendar_new ();
  calendar_data.window = calendar;
  calendar_set_flags (&calendar_data);
  gtk_calendar_mark_day (GTK_CALENDAR (calendar), 19);
  gtk_container_add (GTK_CONTAINER (frame), calendar);
  g_signal_connect (calendar, "month-changed",G_CALLBACK (calendar_month_changed),&calendar_data);
  g_signal_connect (calendar, "day-selected",G_CALLBACK (calendar_day_selected),&calendar_data);

  g_signal_connect (calendar, "prev-month",G_CALLBACK (calendar_prev_month),&calendar_data);
  g_signal_connect (calendar, "next-month", G_CALLBACK (calendar_next_month),&calendar_data);
  g_signal_connect (calendar, "prev-year",G_CALLBACK (calendar_prev_year),&calendar_data);
  g_signal_connect (calendar, "next-year", G_CALLBACK (calendar_next_year), &calendar_data);


  separator = gtk_vseparator_new ();
  gtk_box_pack_start (GTK_BOX (hbox), separator, FALSE, TRUE, 0);

  vbox2 = gtk_vbox_new (FALSE, DEF_PAD);
  gtk_box_pack_start (GTK_BOX (hbox), vbox2, FALSE, FALSE, DEF_PAD);

  /* Build the Right frame with the flags in */

  frame = gtk_frame_new ("Calendar Fin");
  gtk_box_pack_start (GTK_BOX (vbox2), frame, TRUE, TRUE, DEF_PAD);
  calendar2=gtk_calendar_new ();
  calendar2_data.window = calendar2;
  calendar_set_flags (&calendar2_data);
  gtk_calendar_mark_day (GTK_CALENDAR (calendar2), 19);
  gtk_container_add (GTK_CONTAINER (frame), calendar2);
  g_signal_connect (calendar2, "month-changed",G_CALLBACK (calendar_month_changed),&calendar2_data);
  g_signal_connect (calendar2, "day-selected",G_CALLBACK (calendar_day_selected),&calendar2_data);

  g_signal_connect (calendar2, "prev-month",G_CALLBACK (calendar_prev_month),&calendar2_data);
  g_signal_connect (calendar2, "next-month", G_CALLBACK (calendar_next_month),&calendar2_data);
  g_signal_connect (calendar2, "prev-year",G_CALLBACK (calendar_prev_year),&calendar2_data);
  g_signal_connect (calendar2, "next-year", G_CALLBACK (calendar_next_year), &calendar2_data);



  frame = gtk_frame_new ("Signal events");
  gtk_box_pack_start (GTK_BOX (vbox), frame, TRUE, TRUE, DEF_PAD);

  vbox2 = gtk_vbox_new (TRUE, DEF_PAD_SMALL);
  gtk_container_add (GTK_CONTAINER (frame), vbox2);


  hbox = gtk_hbox_new (FALSE, 3);
  gtk_box_pack_start (GTK_BOX (vbox2), hbox, FALSE, TRUE, 0);
  label = gtk_label_new ("Debut :");
  gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, TRUE, 0);
  calendar_data.last_sig = gtk_label_new ("");
  gtk_box_pack_start (GTK_BOX (hbox), calendar_data.last_sig, FALSE, TRUE, 0);



  hbox = gtk_hbox_new (FALSE, 3);
  gtk_box_pack_start (GTK_BOX (vbox2), hbox, FALSE, TRUE, 0);
  label = gtk_label_new ("Fin :");
  gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, TRUE, 0);
  calendar2_data.last_sig = gtk_label_new ("");
  gtk_box_pack_start (GTK_BOX (hbox), calendar2_data.last_sig, FALSE, TRUE, 0);

  bbox = gtk_hbutton_box_new ();
  gtk_box_pack_start (GTK_BOX (vbox), bbox, FALSE, FALSE, 0);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (bbox), GTK_BUTTONBOX_END);




  GSList *premier = NULL;
//  GSList *ignore = NULL;
  premier = g_slist_append(premier, calendar_data.last_sig);
//  ignore = g_slist_append(premier,(GtkWidget*) calendar2_data.last_sig);
//  ignore = g_slist_append(premier,(GtkWidget *) vbox);
//  ignore = g_slist_append(premier,(GtkWidget *) window);

  button = gtk_button_new_with_label ("Valider");
  g_signal_connect (button, "clicked", G_CALLBACK (verifie_selection),premier );

  button2 = gtk_button_new_with_label ("Retour");
  g_signal_connect (button2, "clicked", G_CALLBACK (gtk_main_quit), NULL );
  gtk_container_add (GTK_CONTAINER (bbox), button);
  gtk_container_add (GTK_CONTAINER (bbox), button2);
  GTK_WIDGET_SET_FLAGS (button, GTK_CAN_DEFAULT);
  GTK_WIDGET_SET_FLAGS (button2, GTK_CAN_DEFAULT);
  gtk_widget_grab_default (button2);
  gtk_widget_grab_default (button);

  gtk_widget_show_all (window);
}


/*int main (int argc,char *argv[])
{


  gtk_init (&argc, &argv);
  GtkWidget *window;

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "GtkCalendar Example");
  gtk_container_set_border_width (GTK_CONTAINER (window), 5);
  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
  g_signal_connect (window, "delete-event", G_CALLBACK (gtk_false), NULL);
  gtk_window_set_resizable (GTK_WINDOW (window), FALSE);

  create_calendar ("Selectionnez date",window);

  gtk_main ();

  return 0;
}*/
