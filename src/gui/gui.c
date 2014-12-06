#ifndef NOGUI

#include "gui.h"

/* Récupère le nom de fichier sélectionné et l'affiche sur la console. */

void file_ok_sel (GtkFileSelection *fs)
{
    g_print ("%s\n", gtk_file_selection_get_filename (GTK_FILE_SELECTION (fs)));
}

void OnDestroy();

int gui_main (int argc, char *argv[])
{

    /* Main Windows */
    GtkWidget *window;

    /* Buttons and menus for the header files */
    GtkWidget *quit;
    GtkWidget *open;
    GtkWidget *save_txt;
    GtkWidget *save_filters;
    GtkWidget *binarize;
    GtkWidget *filters_menu;
    GtkWidget *segmentation;
    GtkWidget *start_recognition;
    GtkWidget *menu[8];

    /* Table */
    GtkWidget *table;



    /* Image */
    GtkWidget *image;

    gtk_init(&argc,&argv);

    /* Création de la fenêtre */
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    /* Connexion du signal "destroy" */
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(OnDestroy), NULL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window),
			 "OCAML - Optical Character Analysis ans Machine Learning");
    /* Affichage de la fenêtre */
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    /*table*/
    table = gtk_table_new(10, 10, TRUE);
    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(table));

    /* Label init*/
    open  = gtk_label_new("open");
    quit = gtk_button_new_with_label("Quitter");
    save_txt = gtk_label_new("save text");
    save_filters = gtk_label_new("save image");
    binarize = gtk_label_new("binarize");
    filters_menu = gtk_label_new("filters");
    segmentation = gtk_label_new("segmentation");
    start_recognition = gtk_label_new("recognition");

    menu[0] = open;
    menu[1] = save_txt;
    menu[2] = save_filters;
    menu[3] = binarize;
    menu[4] = filters_menu;
    menu[5] = segmentation;
    menu[6] = start_recognition;
    menu[7] = quit;

    gtk_table_attach(GTK_TABLE(table), menu[0],
		     0, 1,
		     0, 1,
		     GTK_EXPAND | GTK_FILL, GTK_EXPAND,
		     0, 0);
    gtk_table_attach(GTK_TABLE(table), menu[1],
                     1, 2,
                     0, 1,
                     GTK_EXPAND | GTK_FILL, GTK_EXPAND,
                     0, 0);
    gtk_table_attach(GTK_TABLE(table), menu[2],
                     2, 3,
                     0, 1,
                     GTK_EXPAND | GTK_FILL, GTK_EXPAND,
                     0, 0);
    gtk_table_attach(GTK_TABLE(table), menu[3],
                     3, 4,
                     0, 1,
                     GTK_EXPAND | GTK_FILL, GTK_EXPAND,
                     0, 0);
    gtk_table_attach(GTK_TABLE(table), menu[4],
                     4, 5,
                     0, 1,
                     GTK_EXPAND | GTK_FILL, GTK_EXPAND,
                     0, 0);
    gtk_table_attach(GTK_TABLE(table), menu[5],
                     5, 6,
                     0, 1,
                     GTK_EXPAND | GTK_FILL, GTK_EXPAND,
                     0, 0);
    gtk_table_attach(GTK_TABLE(table), menu[6],
                     6, 7,
                     0, 1,
                     GTK_EXPAND | GTK_FILL, GTK_EXPAND,
                     0, 0);
    gtk_table_attach(GTK_TABLE(table), menu[7],
                     8, 9,
                     0, 1,
                     GTK_EXPAND | GTK_FILL, GTK_EXPAND,
                     0, 0);

    g_signal_connect(G_OBJECT(quit), "clicked", G_CALLBACK(OnDestroy), NULL);

    /* Image */

    image = gtk_image_new();
    gtk_image_set_from_file(GTK_IMAGE(image), "seg.png");

    gtk_table_attach(GTK_TABLE(table), image,
                     0, 5,
                     1, 10,
                     GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL,
                     0, 0);

    gtk_widget_show_all(window);
    /* Demarrage de la boucle evenementielle */
    gtk_main();

    return EXIT_SUCCESS;
}

void OnDestroy()
{
    /* Arret de la boucle evenementielle */
    gtk_main_quit();
}


#endif
