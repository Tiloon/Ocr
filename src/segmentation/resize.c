#include "resize.h"

char* to16(struct s_binarypic *picture, struct s_rectangle *orig) {
    char *car = calloc(16*16, sizeof(char));
    unsigned int i;
    unsigned int j;

    for(i=orig->y;i<orig->y+orig->h;i++)
    {
        for(j=orig->x;j<orig->x+orig->w;j++)
        {
            if(car[i*16+j])
                car[i*16+j] = picture->pixels[i+picture->w + j 
                    + ((i-orig->y)*orig->w/16)*picture->w 
                        + (j-orig->x)*orig->h/16];
        }
    }

    for(i=orig->y;i<orig->y+orig->h;i++)
    {
        for(j=orig->x;j<orig->x+orig->w;j++)
        {
            if(car[i*16+j])
                car[i*16+j] = picture->pixels[i+picture->w + j 
                    + ((i-orig->y)*orig->w/16)*picture->w 
                        + (j-orig->x)*orig->h/16];
        }
    }
    return car;
}
