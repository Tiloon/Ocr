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


//Image that will be analysed
GtkWidget  *image2;
GtkWidget *image;
GdkPixbuf *pix2, *pix;
GError *error = NULL;
GError *error2 = NULL;
static GtkWidget *pToolbar = NULL;

int gui_main(int argc,char **argv)
{
    //Variables
    GtkWidget* window = NULL;
    GtkWidget *vBox;	
    GtkWidget *hBox;
    GtkWidget *frame1, *frame2;
    
    //initialisation de gtk+
    gtk_init(&argc,&argv);
    
    //creation d'une fenetre normale, la fenetre principale
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    //Titre de notre fenetre
    gtk_window_set_title(GTK_WINDOW(window), "Text RECO");
    
    //On definit les dimensions de notre fenetre principale
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 800);
    gtk_window_set_resizable (GTK_WINDOW(window), TRUE);
    gtk_window_maximize (GTK_WINDOW(window));
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
    
    /* 
     *
     * TOOL BAR
     *
     *
     *
     */

    /* 
     * Open
     */
    gtk_toolbar_insert_stock(GTK_TOOLBAR(pToolbar),
			     GTK_STOCK_OPEN,
			     "Ouvrir",
			     NULL,
			     G_CALLBACK(load_image),
			     NULL,
			     -1);
    /* Separator*/
    gtk_toolbar_append_space(GTK_TOOLBAR(pToolbar));
    
    /*
     * Filters
     */
    gtk_toolbar_insert_stock(GTK_TOOLBAR(pToolbar),
                             GTK_STOCK_MEDIA_RECORD,
                             "Binarize",
                             NULL,
                             G_CALLBACK(binarize),
                             NULL,
                             -1);
    gtk_toolbar_insert_stock(GTK_TOOLBAR(pToolbar),
                             GTK_STOCK_FIND,
                             "Check rotation",
                             NULL,
                             G_CALLBACK(check_rotation),
                             NULL,
                             -1);
    gtk_toolbar_insert_stock(GTK_TOOLBAR(pToolbar),
                             GTK_STOCK_FIND_AND_REPLACE,
                             "Gaussian filter",
                             NULL,
                             G_CALLBACK(gaussian_filter),
                             NULL,
                             -1);
    gtk_toolbar_insert_stock(GTK_TOOLBAR(pToolbar),
                             GTK_STOCK_APPLY,
                             "Apply all filters",
                             NULL,
                             G_CALLBACK(all_filters),
                             NULL,
                             -1);
    
    /* Separator */
    gtk_toolbar_append_space(GTK_TOOLBAR(pToolbar));

    gtk_toolbar_insert_stock(GTK_TOOLBAR(pToolbar),
                             GTK_STOCK_SELECT_FONT,
                             "Start segmentation",
                             NULL,
                             G_CALLBACK(segmentation),
                             NULL,
                             -1);
    /* Separator */
    gtk_toolbar_append_space(GTK_TOOLBAR(pToolbar));

    gtk_toolbar_insert_stock(GTK_TOOLBAR(pToolbar),
                             GTK_STOCK_EXECUTE,
                             "Start recognition",
                             NULL,
                             G_CALLBACK(start_recognition),
                             NULL,
                             -1);
    /* Separator */
    gtk_toolbar_append_space(GTK_TOOLBAR(pToolbar));

    gtk_toolbar_insert_stock(GTK_TOOLBAR(pToolbar),
                             GTK_STOCK_CLOSE,
                             "Clean window",
                             NULL,
                             G_CALLBACK(clean),
                             NULL,
                             -1);
    gtk_toolbar_insert_stock(GTK_TOOLBAR(pToolbar),
                             GTK_STOCK_FLOPPY,
                             "Save recognized text into \"text.txt\"",
                             NULL,
                             G_CALLBACK(save_text),
                             NULL,
                             -1);
    /* Separator */
    gtk_toolbar_append_space(GTK_TOOLBAR(pToolbar));

    gtk_toolbar_insert_stock(GTK_TOOLBAR(pToolbar),
                             GTK_STOCK_QUIT,
                             "Close",
                             NULL,
                             G_CALLBACK(quit),
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
    pix = gdk_pixbuf_new_from_file_at_size(NULL, 1000/2, 1000/2, &error2);
    image = gtk_image_new_from_pixbuf(pix);
    gtk_container_add(GTK_CONTAINER(frame2), image);       
    
    pix2 = gdk_pixbuf_new_from_file_at_size (NULL,
					    1000 / 2,
					    1000 / 2,
					    &error);
    image2 = gtk_image_new_from_pixbuf(pix2);
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
	    picture_load_from_file(path);
	    pix2 = gdk_pixbuf_new_from_file_at_size (path,
						    1000 / 2,
						    1000 / 2,
						    &error);
	    
	    gtk_image_set_from_pixbuf(GTK_IMAGE(image2), pix2);
	    g_free(path);
	}
	gtk_widget_destroy(file);
}

void binarize()
{
    struct s_binarypic *pic = calloc(1, sizeof(struct s_binarypic));
    gdk_to_binary(picture_get_image(), pic);
    binary_to_gdk(pic, picture_get_pimage());
    pix2 = gdk_pixbuf_scale_simple (picture_get_image(), 
			     gdk_pixbuf_get_width (pix2), 
			     gdk_pixbuf_get_height (pix2), 
			     GDK_INTERP_NEAREST); 
    gtk_image_set_from_pixbuf(GTK_IMAGE(image2), pix2);
}

void apply_gaussian_filter()
{
    filter_add("gaussian_filter");
}

void check_rotation()
{
    filter_add("rot_filter");
}

void segmentation()
{
    int width, height;
    FLAGS->segmentation_output = "segmentation_output.png";
    width = gdk_pixbuf_get_width(pix2);
    height = gdk_pixbuf_get_height (pix2);
    pix2 = perform_ocr(picture_get_image());
    pix2 = gdk_pixbuf_scale_simple (picture_get_image(),
				    gdk_pixbuf_get_width (pix2),
				    gdk_pixbuf_get_height (pix2),
				    GDK_INTERP_NEAREST);
    gtk_image_set_from_pixbuf(GTK_IMAGE(image2), pix2);
}

void all_filters()
{
    filters_apply_all(&pix2);    
    pix2 = perform_ocr(pix2);
}

void start_recognition()
{
    pix2 = perform_ocr(pix2);
}

void save_text()
{
}
void clean()
{
    gtk_widget_destroy(image2);
    gtk_widget_destroy(image);
}
void quit()
{
    gtk_main_quit();
}
