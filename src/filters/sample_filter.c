#include "filters.h"
#include "sample_filter.h"
#include "../main.h"

int sample_filter(GdkPixbuf *picture, size_t nb_params, char **params)
{
    int ht, wt;
    int i, j;
    int rowstride;
    int bpp;
    unsigned int grayscale;
    guchar *pixel;

    if(FLAGS->verbosity && nb_params >= 1)
        printf("Filter parameters : \"%s\"\n", params[0]);

    printf("%zu\n", nb_params);
    if(gdk_pixbuf_get_bits_per_sample(picture) != 8)
        return 1;
    //look at 3 bytes per pixel.
    //getting attributes of height,
    ht = gdk_pixbuf_get_height(picture);
    //width, and bpp.Also get pointer
    wt = gdk_pixbuf_get_width(picture);
    //to pixels.
    pixel = gdk_pixbuf_get_pixels(picture);
    bpp = gdk_pixbuf_get_n_channels(picture);
    rowstride = wt * bpp;
    for(i = 0; i < ht; i++) //iterate over the height of image.
    {
        for(j = 0; j < rowstride; j += bpp)
            //read every pixel in the row.skip//bpp bytes
        {
            grayscale = pixel[i * rowstride + j];
            grayscale += pixel[i * rowstride + j + 1];
            grayscale += pixel[i * rowstride + j + 2];
            //access pixel[i][j] as
            // pixel[i*rowstride + j]
            //access red,green and blue as
            //pixel[i*rowstride + j+0]=0;
            //pixel[i*rowstride + j+1]=0;
            //pixel[i*rowstride + j+2]=blue
            if(grayscale < 0xFF*3/2)
                grayscale = 0;
            else
                grayscale = ~0;

            pixel[i * rowstride + j] = grayscale;
            pixel[i * rowstride + j + 1] = grayscale;
            pixel[i * rowstride + j + 2] = grayscale;
        }
    }

    return 0;
}
