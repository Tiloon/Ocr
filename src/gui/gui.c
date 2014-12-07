#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "gui.h"
#include "../main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <locale.h>
#include <wchar.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include "../redef.h"
#include "../picture/copy_binarized.h"
#include "../picture/binarypic.h"
#include "../picture/loader.h"
#include "../filters/filters.h"
#include "../picture/convert_pic.h"
#include "../perform_ocr.h"
#include "../help/help.h"
#include "../improvements/dictionary.h"


//Image that will be analysed
GtkWidget  *image2;
GdkPixbuf *pix;
GError *error = NULL;
static GtkWidget *pToolbar = NULL;

int gui_main(int argc,char **argv)
{
    //Variables
    GtkWidget* window = NULL;
    
    
    GtkWidget *vBox;	
    GtkWidget *hBox;
    GtkWidget *frame1, *frame2;
    GtkWidget *image;

    //initialisation de gtk+
    gtk_init(&argc,&argv);
    
    //creation d'une fenetre normale, la fenetre principale
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    //Titre de notre fenetre
    gtk_window_set_title(GTK_WINDOW(window), "Text RECO");
    
    //On definit les dimensions de notre fenetre principale
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 800);
    
    //On place la fenetre au centre de l'ecran
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
    
    //On connecte la fenetre a destroy, pour quitter la fenetre 
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    //On place notre box principale dans la fenetre
    vBox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vBox);
    
    /* Création de la barre d'outils */
    pToolbar = gtk_toolbar_new();
    gtk_box_pack_start(GTK_BOX(vBox), pToolbar, FALSE, FALSE, 0);
    
    /* Création à partir de stock */
    gtk_toolbar_insert_stock(GTK_TOOLBAR(pToolbar),
			     GTK_STOCK_OPEN,
			     "Ouvrir",
			     NULL,
			     G_CALLBACK(load_image),
			     NULL,
			    -1);
    gtk_toolbar_insert_stock(GTK_TOOLBAR(pToolbar),
			     GTK_STOCK_QUIT,
			     "Fermer",
			     NULL,
			     G_CALLBACK(gtk_main_quit),
			     NULL,
			     -1);
    
	/* Insertion d'un espace */
	gtk_toolbar_append_space(GTK_TOOLBAR(pToolbar));
 
	/* Création a partir de stock */
	gtk_toolbar_insert_stock(GTK_TOOLBAR(pToolbar),
			    GTK_STOCK_GO_FORWARD,
			    "Binarize",
			    NULL,
			    G_CALLBACK(binarize),
			    NULL,
			    -1);
	gtk_toolbar_insert_stock(GTK_TOOLBAR(pToolbar),
			    GTK_STOCK_GO_DOWN,
			    "Blockseg",
			    NULL,
			    G_CALLBACK(blockseg),
			    NULL,
			    -1);
	gtk_toolbar_insert_stock(GTK_TOOLBAR(pToolbar),
			    GTK_STOCK_GO_DOWN,
			    "Lineseg",
			    NULL,
			    G_CALLBACK(lineseg),
			       NULL,
			       -1);
	gtk_toolbar_insert_stock(GTK_TOOLBAR(pToolbar),
			    GTK_STOCK_GO_DOWN,
			    "Clean",
			    NULL,
			    G_CALLBACK(clean),
			     NULL,
			     -1);
	/* Modification de la taille des icônes */
	gtk_toolbar_set_icon_size(GTK_TOOLBAR(pToolbar),
			     GTK_ICON_SIZE_BUTTON);
	/* Affichage uniquement des icônes */
	gtk_toolbar_set_style(GTK_TOOLBAR(pToolbar),
			 GTK_TOOLBAR_ICONS);


	//la hBox2 contient les bouttons        
        




	//hBox contenant la frame1 et la frame2
	hBox = gtk_hbox_new(TRUE, 0);
	frame1 = gtk_frame_new("Test1");
	frame2 = gtk_frame_new("Test2");
	gtk_box_pack_start(GTK_BOX(hBox), frame1, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(hBox), frame2, TRUE, TRUE, 0);

	//contenu de la frame1
	//Chargement d'une image a partir d'un fichier
	image = gtk_image_new_from_file(NULL);
	gtk_container_add(GTK_CONTAINER(frame2), image);       
        
	pix = gdk_pixbuf_new_from_file_at_size (NULL,
					     1000 / 2,
					     1000 / 2,
					     &error);
	image2 = gtk_image_new_from_pixbuf(pix);
	gtk_container_add(GTK_CONTAINER(frame1), image2);

	//Contenu de la  vBox (Box principale)

	gtk_box_pack_start(GTK_BOX(vBox), hBox, TRUE, TRUE, 0);

	//Permet d'afficher tous les widgets contenu dans cette fenetre
        gtk_widget_show_all(window);
	//Boucle principale
	gtk_main();

    return EXIT_SUCCESS;
}



void load_image()
{
    GtkWidget *file;
    GtkWidget *parent;
    gchar *path;

    parent = GTK_WIDGET(NULL);
    file = gtk_file_chooser_dialog_new
	("Ouvrir",
	 GTK_WINDOW(parent),
	 GTK_FILE_CHOOSER_ACTION_OPEN,
	 GTK_STOCK_CANCEL,
	 GTK_RESPONSE_CANCEL,
	 GTK_STOCK_OPEN,
	 GTK_RESPONSE_OK,
	 NULL);
    
        gtk_window_set_modal(GTK_WINDOW(file),TRUE);
        if(gtk_dialog_run(GTK_DIALOG(file)))
	{
	    path = gtk_file_chooser_get_filename
		(GTK_FILE_CHOOSER(file));
	    pix = gdk_pixbuf_new_from_file_at_size (path,
						    1000 / 2,
						    1000 / 2,
						    &error);
	    
	    gtk_image_set_from_pixbuf(GTK_IMAGE(image2), pix);
	    g_free(path);
	}
	gtk_widget_destroy(file);
}

void binarize()
{
    gtk_image_set_from_file(GTK_IMAGE(image2), "binarisation.bmp");
}
void blockseg()
{
    //segment_and_save(picture_get_image());
    gtk_image_set_from_file(GTK_IMAGE(image2), "seg.png");
    
}
void lineseg()
{
    gtk_image_set_from_file(GTK_IMAGE(image2), "Lineseg.bmp");
}
void clean()
{
    gtk_image_set_from_file(GTK_IMAGE(image2), NULL);
}
