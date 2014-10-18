#include "mask.h"

char* mask_picture(char to_mask, struct s_binarypic *picture, char *mask);
{
    char *pixel_array;
    uint i;

    pixel_array = malloc(picture->w * picture->h * sizeof(char));

    for(i = 0; i < (picture->w * picture->h); i++)
    {
        if(mask[i] == to_mask)
            pixel_array[i] = picture->pixels[i];
        else
            pixel_array[i] = 0;
    }

    return pixel_array;
}

