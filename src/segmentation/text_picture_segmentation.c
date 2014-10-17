#include "text_picture_segmentation.h"

/* Documentation :
** - Bukhari-text-image-segmentation-DRR11.pdf
**
*/

char threshold_reduction(char px00, char px01, char px10, char px11, char t);
int subsample_pic(char t, char **pic, uint *w, uint *h);
int expansion_1x4(char **pic, uint *w, uint *h);

char threshold_reduction(char px00, char px01, char px10, char px11, char t)
{
    return (px00 + px01 + px10 + px11) >= t;
}

int subsample_pic(char t, char **pic, uint *w, uint *h)
{
    uint i, j;

    (*w) /= 2;
    (*h) /= 2;

    for(j = 0; j < (*h); j++)
    {
        for(i = 0; i < (*w); i++)
        {
            (*pic)[j * (*w) + i] = threshold_reduction(
                    (*pic)[(j * 2 * (*w) + i) * 2],
                    (*pic)[(j * 2 * (*w) + i) * 2 + 1],
                    (*pic)[((j * 2 * + 1) * (*w) + i) * 2],
                    (*pic)[((j * 2 * + 1) * (*w) + i) * 2 + 1],
                    t);
        }
    }

    // Maybe/maybe not
    //*pic = realloc(*pic, (*w) * (*h) * sizeof(char));
    //if(pic == NULL)
    //    return 1;

    return 0;
}

int expansion_1x4(char **pic, uint *w, uint *h)
{
    int i, j;

    // Maybe/maybe not
    //*pic = realloc(*pic, (*w) * (*h) * 4 * sizeof(char));
    //if(pic == NULL)
    //    return 1;

    for(j = (*h) - 1; j >= 0; j--)
    {
        for(i = (*w) - 1; i >= 0; i--)
        {
            (*pic)[((j + 1) * (*w)) * 2 + i * 2 + 1] = (*pic)[j * (*w) + i];
            (*pic)[((j + 1) * (*w)) * 2 + i * 2] = (*pic)[j * (*w) + i];
            (*pic)[(j * (*w)) * 2 + i * 2 + 1] = (*pic)[j * (*w) + i];
            (*pic)[(j * (*w)) * 2 + i * 2] = (*pic)[j * (*w) + i];
        }
    }

    (*w) *= 2;
    (*h) *= 2;

    return 0;
}

int text_image_segmentation(char *pic, uint w, uint h, char **mask)
{
    char *seed;

    (*mask) = realloc(*mask, (w + 1) * (h + 1) * sizeof(char));
    memcpy(*mask, pic, (w + 1) * (h + 1));


    subsample_pic(1, mask, &w, &h);
    subsample_pic(1, mask, &w, &h);

    // Hole filling morpho logical operation

    seed = malloc((w + 1) * (h + 1) * sizeof(char));
    memcpy(seed, *mask, (w + 1) * (h + 1));


    subsample_pic(4, &seed, &w, &h);
    subsample_pic(3, &seed, &w, &h);

    // Opening with SE=5x5
    morph_open(seed, w, h, 2, 2);

    expansion_1x4(&seed, &w, &h);
    expansion_1x4(&seed, &w, &h);

    // Here we have the seed image

    // Union of overlapping components
    // mask = overlapping_components(mask, seed);

    // dilation with SE=3x3
    morph_dilate(*mask, w, h, 1, 1);

    expansion_1x4(mask, &w, &h);
    expansion_1x4(mask, &w, &h);

    return 0;
}
