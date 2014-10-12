#include "filters.h"
#include "sample_filter.h"

int sample_filter(GdkPixbuf *picture, char *parameters)
{
    unsigned int i, j, channels, height, width, grey;
    guchar *pixels;

    printf("%s", parameters);
    channels = gdk_pixbuf_get_n_channels(picture);
    width = gdk_pixbuf_get_width(picture);
    height = gdk_pixbuf_get_height(picture);
    pixels = gdk_pixbuf_get_pixels(picture);

    // check if we have only 24bpp (3channels, no alpha)
    if(channels != 3 ||
        gdk_pixbuf_get_bits_per_sample(picture) != 8)
    {
        print_filter_error("sample_filter only allow 24bpp pictures"
            "(3chanels)", sample_filter_name);
        return 1;
    }

    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            grey = pixels[i * width + j * channels];
            grey += pixels[i * width + j * channels + 1];
            grey += pixels[i * width + j * channels + 2];
            grey = grey / 3;

            pixels[i * width + j * channels] = grey;
            pixels[i * width + j * channels] = grey;
            pixels[i * width + j * channels] = grey;
        }
    }

    return 0;
}
