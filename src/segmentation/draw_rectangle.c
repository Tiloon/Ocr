#include "draw_rectangle.h"

int draw_rectangle(GdkPixbuf *picture, struct s_rectangle rect, guchar r,
        guchar g, guchar b)
{
    int i, j, wt, ht;
    int rowstride;
    int bpp;
    unsigned int grayscale;
    guchar *pixel;

    if(gdk_pixbuf_get_bits_per_sample(picture)!=8)
        return 1;

    ht = gdk_pixbuf_get_height(picture);
    wt = gdk_pixbuf_get_width(picture);
    pixel = gdk_pixbuf_get_pixels(picture);
    bpp = 3;
    rowstride = wt * bpp;

    for(i = rect.y; i < (rect.h + rect.y); i++)
    {
        if(i > ht)
            break;
        //printf("y : %i, x : %i\n", i,  rect.w );
        pixel[i * rowstride + rect.x * 3] = r;
        pixel[i * rowstride + rect.x * 3 + 1] = g;
        pixel[i * rowstride + rect.x * 3 + 2] = b;

        pixel[i * rowstride + (rect.x + rect.w) * 3] = r;
        pixel[i * rowstride + (rect.x + rect.w) * 3 + 1] = g;
        pixel[i * rowstride + (rect.x + rect.w) * 3 + 2] = b;
    }

    for(i = rect.x; i < (rect.x + rect.w); i++)
    {
        pixel[rect.y * rowstride + i * 3] = r;
        pixel[rect.y * rowstride + i * 3  + 1] = g;
        pixel[rect.y * rowstride + i * 3 + 2] = b;

        pixel[(rect.h + rect.y) * rowstride + i * 3] = r;
        pixel[(rect.h + rect.y) * rowstride + i * 3 + 1] = g;
        pixel[(rect.h + rect.y) * rowstride + i * 3 + 2] = b;
    }
    return 0;
}
