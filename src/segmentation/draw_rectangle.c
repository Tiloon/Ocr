#include "draw_rectangle.h"

int draw_rectangle(GdkPixbuf *picture, struct s_rectangle rect, guchar r,
        guchar g, guchar b)
{
    unsigned int i, wt, ht;
    int rowstride;
    int bpp;
    guchar *pixel;

    if((gdk_pixbuf_get_bits_per_sample(picture)!=8) &&
            !gdk_pixbuf_get_has_alpha(picture))
        return 1;

    ht = gdk_pixbuf_get_height(picture);
    wt = gdk_pixbuf_get_width(picture);
    pixel = gdk_pixbuf_get_pixels(picture);
    bpp = gdk_pixbuf_get_n_channels(picture);
    rowstride = wt * bpp;

    for(i = rect.y; i < (rect.h + rect.y); i++)
    {
        if(i > ht)
            break;
        //printf("y : %i, x : %i\n", i,  rect.w );
        pixel[i * rowstride + rect.x * bpp] = r;
        pixel[i * rowstride + rect.x * bpp + 1] = g;
        pixel[i * rowstride + rect.x * bpp + 2] = b;

        pixel[i * rowstride + (rect.x + rect.w) * bpp] = r;
        pixel[i * rowstride + (rect.x + rect.w) * bpp + 1] = g;
        pixel[i * rowstride + (rect.x + rect.w) * 3 + 2] = b;
    }

    for(i = rect.x; i < (rect.x + rect.w); i++)
    {
        pixel[rect.y * rowstride + i * bpp] = r;
        pixel[rect.y * rowstride + i * bpp  + 1] = g;
        pixel[rect.y * rowstride + i * bpp + 2] = b;

        pixel[(rect.h + rect.y) * rowstride + i * bpp] = r;
        pixel[(rect.h + rect.y) * rowstride + i * bpp + 1] = g;
        pixel[(rect.h + rect.y) * rowstride + i * bpp + 2] = b;
    }
    return 0;
}
