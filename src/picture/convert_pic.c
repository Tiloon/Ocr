#include "convert_pic.h"

int gdk_to_binary(GdkPixbuf *picture, struct s_binarypic *binarypic)
{
    unsigned int i;
    unsigned char *pixel_tab;
    int channels = gdk_pixbuf_get_n_channels(picture);

    binarypic->h = gdk_pixbuf_get_height(picture);
    binarypic->w = gdk_pixbuf_get_width(picture);

    pixel_tab = gdk_pixbuf_get_pixels(picture);

    if(!(binarypic->pixels = calloc((1 + binarypic->w) * (1 + binarypic->h),
                    sizeof(char))))
    {
        fprintf(stderr, "Alloc error %s:%i\n", __FILE__, __LINE__);
        *binarypic->pixels = 0;
        return 1;
    }
    for (i = 0; i < (binarypic->h * binarypic->w); i++)
    {
        binarypic->pixels[i] =
            (pixel_tab[i * channels] / 3) +
            (pixel_tab[i * channels + 1] / 3) +
            (pixel_tab[i * channels + 2] / 3) >= 0x7F;
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
    if(!(*picture = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, binarypic->w,
            binarypic->h)))
    {
        LOG_ALLOC_ERR();
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
