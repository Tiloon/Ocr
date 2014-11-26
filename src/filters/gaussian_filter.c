#include "filters.h"
#include "gaussian_filter.h"
#include "../main.h"

// This is a gaussian blur filter using the box blur multipass approximation


int horizontal_box_blur(unsigned int *in, unsigned int *out, size_t height,
        size_t width, size_t size)
{
    size_t i, j;
    size_t k;
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            out[i * width + j] += in[i * width + j];
            for(k = 1; k < size * 2; k++)
                out[i * width + j] +=
                    ((i >= k) ? in[(i - k) * width + j] : 0) +
                    ((i + k < height) ? in[(i + k) * width + j] : 0);

            out[i * width + j] /= (i > k ? k : i) +
                (i + k < height ? k : height - i) - 1;

            if(out[i * width + j] > 0xFF)
                out[i * width + j] = 0xFF;
        }
    }
    return 0;
}

int vertical_box_blur(unsigned int *in, unsigned int *out, size_t height,
        size_t width, size_t bpp, size_t size)
{
    size_t i, j;
    size_t k;
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            out[i * width + j] += in[i * width + j];
            for(k = 1; k < size * bpp; k += bpp)
                out[i * width + j] +=
                    (((/*j*/i >= k) ? in[i * width + j - k] : 0) +
                    ((/*j*/i + k < height) ? in[i * width + j + k] : 0));

            out[i * width + j] /= 1 +
                ((j > k ? k : j) / bpp) +
                ((j + k < width ? k : width - j) / bpp);

            //out[i * width + j] /= 1 + k * 2;
            if(out[i * width + j] > 0xFF)
                out[i * width + j] = 0xFF;
        }
    }
    return 0;
}

int box_blur(unsigned int *in, unsigned int *out, int height, int width,
        int bpp, size_t size)
{
    long i, sze;
    unsigned int *swap;
    sze = ((long) height) * ((long) width);
    for(i = 0; i < sze; i++)
        out[i] = 0;
    horizontal_box_blur(in, out, height, width, size);
    swap = in;
    in = out;
    out = swap;
    vertical_box_blur(in, out, height, width, bpp, size);
    return 0;
}

int gaussian_filter(GdkPixbuf *picture, size_t nb_params, char **params)
{
    int ht, wt;
    int i;
    int rowstride;
    int bpp;
    unsigned int *temp, *temp_out, *swap;
    guchar *pixel;

    if(FLAGS->verbosity && nb_params >= 1)
        printf("Filter parameters : \"%s\"\n", params[0]);

    printf("%zu\n", nb_params);
    if(gdk_pixbuf_get_bits_per_sample(picture)!=8)
        return 1;
    ht = gdk_pixbuf_get_height(picture);
    wt = gdk_pixbuf_get_width(picture);
    pixel = gdk_pixbuf_get_pixels(picture);
    bpp = 3;
    rowstride = wt * bpp;
    if(!((temp = calloc(wt * bpp * ht, sizeof(unsigned int))) &&
        (temp_out = calloc(wt * bpp * ht, sizeof(unsigned int)))))
    {
        FREE(temp);
        LOG_ALLOC_ERR();
        return 1;
    }
    for(i = 0; i < ht * rowstride; i++)
        temp[i] = pixel[i];
    if((ht < 1) || (rowstride < 1) || (bpp < 1))
        return 1;
    for(i = 0; i < 3; i++)
    {
        box_blur(temp, temp_out, ht, rowstride, bpp, 1);

        // We swap buffer
        swap = temp_out;
        temp_out = temp;
        temp = swap;
    }
    for(i = 0; i < ht * rowstride; i++)
        pixel[i] = temp[i];

    FREE(temp);
    FREE(temp_out);

    return 0;
}
