#include "morphology.h"

/*
 * Documentation :
 * - http://en.wikipedia.org/wiki/Mathematical_morphology
 * - http://en.wikipedia.org/wiki/Erosion_(morphology)
 * - http://en.wikipedia.org/wiki/Dilation_(morphology)
 * - http://ostermiller.org/dilate_and_erode.html
 *
 */


int morph_vertical(char base, char *pic, uint w, uint h, uint x);
int morph_horizontal(char base, char *pic, uint w, uint h, uint y);

// erode(a, b) = a - b
int morph_erode(char *pic, uint w, uint h, uint x, uint y)
{
    // We use the relation a - (x, y) = a - (x, 1) - (1, y)
    return morph_vertical(0, pic, w, h, x) ||
        morph_horizontal(0, pic, w, h, y);
}

// dilate(a, b) = a + b
int morph_dilate(char *pic, uint w, uint h, uint x, uint y)
{
    // We use the relation a + (x, y) = a + (x, 1) + (1, y)
    return morph_vertical(1, pic, w, h, x) ||
        morph_horizontal(1, pic, w, h, y);
}

// close(a, b) = (a + b) - b
int morph_close(char *pic, uint w, uint h, uint x, uint y)
{
    return morph_dilate(pic, w, h, x, y) ||
        morph_erode(pic, w, h, x, y);
}

// open(a, b) = (a - b) + b
int morph_open(char *pic, uint w, uint h, uint x, uint y)
{
    return morph_erode(pic, w, h, x, y) ||
        morph_dilate(pic, w, h, x, y);
}

int morph_vertical(char base, char *pic, uint w, uint h, uint x)
{
    uint i, j, k;

    for(j = 0; j < h; j++)
    {
        for(i = 0; i < w; i++)
        {
            if(pic[j * w + i] == base)
            {
                if(i < x)
                {
                    k = i;
                    i = 0;
                }
                else
                {
                    k = x;
                    i -= x;
                }

                for(k += x; k != 0; k--)
                {
                    i++;
                    if(i < w)
                        pic[j * w + i] = base;
                }
                i += x;
            }
        }
    }

    return 0;
}

int morph_horizontal(char base, char *pic, uint w, uint h, uint y)
{
    uint i, j, k;

    for(i = 0; i < w; i++)
    {
        for(j = 0; j < h; j++)
        {
            if(pic[j * w + i] == base)
            {
                if(j < y)
                {
                    k = j;
                    j = 0;
                }
                else
                {
                    k = y;
                    j -= y;
                }

                for(k += y; k != 0; k--)
                {
                    j++;
                    if(j < h)
                        pic[j * w + i] = base;
                }
                j += y;
            }
        }
    }

    return 0;
}
