#include "convert_pic.h"

int gdk_to_binary(GdkPixbuf *picture, struct s_binarypic *binarypic)
{
    unsigned int i;
    unsigned char *pixel_tab;
    binarypic->h = gdk_pixbuf_get_height(picture);
    binarypic->w = gdk_pixbuf_get_width(picture);

    pixel_tab = gdk_pixbuf_get_pixels(picture);

    binarypic->pixels = malloc((1 + binarypic->w) * (1 + binarypic->h) * sizeof(char));

    for (i = 0; i < (binarypic->h * binarypic->w); i++)
    {
        //printf("x : %i, y : %i", i % binarypic->pixels
        binarypic->pixels[i] =
            (pixel_tab[i* 3] / 3) +
            (pixel_tab[i * 3] / 3) +
            (pixel_tab[i * 3] / 3) >= 1;
    }

    return 0;
}

int binary_to_gdk(struct s_binarypic *binarypic, GdkPixbuf **picture)
{
    unsigned char *pixel_tab;
    unsigned int i;

    if(*picture)
    {
        g_object_unref(*picture);
        while(*picture)
            ;
    }
    *picture = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, binarypic->w,
            binarypic->h);

    if(!picture)
    {
        fprintf(stderr, "Error - Binary_to_Gdk : not enough memory");
        return 1;
    }

    pixel_tab = gdk_pixbuf_get_pixels(*picture);

    for(i = 0; i < (binarypic->h * binarypic->w); i++)
    {
        pixel_tab[i * 3] = (binarypic->pixels[i] ? ~0 : 0);
        pixel_tab[i * 3 + 1] = (binarypic->pixels[i] ? ~0 : 0);
        pixel_tab[i * 3 + 2] = (binarypic->pixels[i] ? ~0 : 0);
    }

    return 0;
}
