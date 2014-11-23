#include "resize.h"

// Debugging purposes :D
#include <stdio.h>
int debug_vectorized_char(char * v)
{
    for(size_t i = 0; i < CHAR_HEIGHT; i++)
    {
        for(size_t j = 0; j < CHAR_WIDTH; j++)
            printf("%i", v[i * CHAR_WIDTH + j]);
        printf("\n");
    }
    printf("\n");
    return 0;
}

char* vectorize_char(struct s_binarypic *picture, struct s_rectangle *orig) {
    char *car = calloc(CHAR_WIDTH * CHAR_HEIGHT, sizeof(char));
    unsigned int i;
    unsigned int j;

    for(i = orig->y; i < orig->y + orig->h; i++)
    {
        for(j = orig->x; j < orig->x + orig->w; j++)
        {
            if(car[i * CHAR_WIDTH + j])
                car[i * CHAR_WIDTH + j] = picture->pixels[i + picture->w + j
                    + ((i - orig->y) * orig->w / 16) * picture->w
                    + (j - orig->x) * orig->h / 16];
        }
    }

    for(i = orig->y; i < orig->y + orig->h; i++)
    {
        for(j = orig->x; j < orig->x + orig->w; j++)
        {
            if(car[i * CHAR_WIDTH + j])
                car[i * CHAR_WIDTH + j] = picture->pixels[i + picture->w + j
                    + ((i - orig->y) * orig->w / 16) * picture->w
                    + (j - orig->x) * orig->h / 16];
        }
    }
    debug_vectorized_char(car);
    return car;
}

