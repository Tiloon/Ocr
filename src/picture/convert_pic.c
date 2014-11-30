#include "convert_pic.h"

static unsigned char * gdk_to_8bit_grayscale(GdkPixbuf *picture)
{
    unsigned char *grayscale, *pixel_tab;
    size_t i, h, w, channels;

    channels = gdk_pixbuf_get_n_channels(picture);
    h = gdk_pixbuf_get_height(picture);
    w = gdk_pixbuf_get_width(picture);

    pixel_tab = gdk_pixbuf_get_pixels(picture);

    if(!(grayscale = calloc((w + 1) * (h + 1), sizeof(unsigned char))))
    {
        LOG_ALLOC_ERR();
        return NULL;
    }

    for (i = 0; i < (h * w); i++)
    {
        grayscale[i] =
            (pixel_tab[i * channels] +
            pixel_tab[i * channels + 1] +
            pixel_tab[i * channels + 2]) / 3;
    }

    return grayscale;
}

static float * make_histogram(unsigned char * grayscale, size_t size)
{
    size_t tmp_histo[256];
    size_t i;
    float *histo;

    for(i = 0; i < size; i++)
        (tmp_histo[grayscale[i]])++;

    if(!(histo = calloc(256, sizeof(float))))
    {
        LOG_ALLOC_ERR();
        return NULL;
    }

    for(i = 0; i < 256; i++)
        histo[i] = ((float) tmp_histo[i]) / ((float) size);

    return histo;
}

static unsigned char get_treshold(float * histo)
{
    // Otsu's method implemenation

    long double sum, sumB, wB, wF, mB, mF,  max, between, threshold1, threshold2;
    size_t i;

    wB = 0;
    sumB = 0;
    sum = 0;
    max = 0;

    for(i = 0; i < 256; i++)
        sum += i * histo[i];

    for(i = 0; i < 256; i++)
    {
        wB += histo[i];
        if(wB == 0)
            continue; // no pixel of color i

        wF = ((long double)1.0) - wB;
        if(wF == 0)
            break; // All pixel have color i

        sumB += i * histo[i];

        mB = sumB / wB;
        mF = (sum - sumB) / wF;
        between = wB * wF * (mB - mF) * (mB - mF);
        if(between >= max)
        {
            threshold1 = i;
            if(between > max)
                threshold2 = i;
            max = between;
        }
    }
    return (unsigned char)((threshold1 + threshold2) * (long double)0x7F);
}

int gdk_to_binary(GdkPixbuf *picture, struct s_binarypic *binarypic)
{
    size_t i;
    unsigned char *grayscale;
    unsigned char threshold;
    float *histogram;

    binarypic->h = gdk_pixbuf_get_height(picture);
    binarypic->w = gdk_pixbuf_get_width(picture);


    if(!(grayscale = gdk_to_8bit_grayscale(picture)))
        return 1;
    if(!(histogram = make_histogram(grayscale, binarypic->h * binarypic->w)))
        return 1;

    threshold = get_treshold(histogram);

    if(!(binarypic->pixels = calloc((1 + binarypic->w) * (1 + binarypic->h),
                    sizeof(char))))
    {
        LOG_ALLOC_ERR();
        *binarypic->pixels = 0;
        return 1;
    }

    for (i = 0; i < (binarypic->h * binarypic->w); i++)
    {
        binarypic->pixels[i] = grayscale[i] >= threshold;
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
