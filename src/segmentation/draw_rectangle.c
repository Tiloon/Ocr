#include "draw_rectangle.h"

int draw_rectangle(GdkPixbuf *picture, struct s_rectangle rect, guchar r,
        guchar g, guchar b)
{
    int i, j, wt;
    int rowstride;
    int bpp;
    unsigned int grayscale;
    guchar *pixel;

    if(gdk_pixbuf_get_bits_per_sample(picture)!=8)
        return 1;

    wt = gdk_pixbuf_get_width(picture);
    pixel = gdk_pixbuf_get_pixels(picture);
    bpp = 3;
    rowstride = wt * bpp;

    for(i = rect.y; i < (rect.y + rect.h); i++)
    {
        pixel[i * rowstride + rect.x] = r;
        pixel[i * rowstride + rect.x + 1] = g;
        pixel[i * rowstride + rect.x + 2] = b;

        pixel[i * rowstride + rect.x + rect.w] = r;
        pixel[i * rowstride + rect.x + rect.w + 1] = g;
        pixel[i * rowstride + rect.x + rect.w + 2] = b;
    }

    return 0;
}
