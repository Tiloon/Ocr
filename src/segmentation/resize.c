#include "resize.h"

struct s_rectangle to16(struct s_rectangle *orig) {
    struct s_rectangle car = calloc(16*16, sizeof(char));
    unsigned int i;
    unsigned int j;

    for(i=0;i<orig->h;i++)
    {
        for(j=0;j<orig->w;j++)
        {
            if(car[i*16+j])
                car[i*16+j] = ori[(i*orig->w/16)*orig->w + j*orig->h/16];
        }
    }

    for(i=0;i<16;i++)
    {
        for(j=0;j<16;j++)
        {
            if(car[i*16+j])
                car[i*16+j] = ori[(i*orig->w/16)*orig->w + j*orig->h/16];
        }
    }
    orig = car;
    return car;
}
