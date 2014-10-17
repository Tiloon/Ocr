#include "imgToBinary.h"


int imgToBinary(GdkPixbuf *picture, struct s_binarypic *binarypic)
{
    unsigned int i, j;
    unsigned char *pixel_tab;
    binarypic->h = gdk_pixbuf_get_height(picture);
    binarypic->w = gdk_pixbuf_get_width(picture);

    pixel_tab = gdk_pixbuf_get_pixels(picture);

    binarypic->pixels = malloc(binarypic->w * binarypic->h * sizeof(char));

    for (i = 0; i < binarypic->h; i++)
    {
        for(j = 0; j < binarypic->w; j++)
        {
            binarypic->pixels[i * binarypic->w + j] =
                (pixel_tab[(i * binarypic->w + j) * 3] / 3) +
                (pixel_tab[(i * binarypic->w + j) * 3 + 1] / 3) +
                (pixel_tab[(i * binarypic->w * j) * 3 + 2] / 3) >= 128;
        }
    }
    return 0;
}
