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
    char *car;
    int A, B, C, D, x, y, index, gray, w2 = CHAR_WIDTH, h2 = CHAR_HEIGHT;
    int w = orig->w;
    int h = orig->h;
    float x_ratio = ((float)(w - 1)) / ((float) w2);
    float y_ratio = ((float)(h - 1)) / ((float) h2);
    float x_diff, y_diff;
    int offset = 0;
    int i, j;
    if(!(car = calloc(CHAR_WIDTH * CHAR_HEIGHT, sizeof(char))))
    {
        LOG_ALLOC_ERR();
        return 0;
    }
    for(i = 0; i < h2; i++)
    {
        for(j = 0; j < w2; j++)
        {
            x = (int)(x_ratio * j);
            y = (int)(y_ratio * i);
            x_diff = (x_ratio * j) - x;
            y_diff = (y_ratio * i) - y;
            index = y * w + x;

            A = picture->pixels[orig->y * picture->w + orig->x
                + index % orig->w + (index / orig->w) * picture->w];
            B = picture->pixels[orig->y * picture->w + orig->x
                + index % orig->w + (index / orig->w) * picture->w + 1];
            C = picture->pixels[orig->y * picture->w + orig->x
                + index % orig->w + (index / orig->w) * picture->w + w];
            D = picture->pixels[orig->y * picture->w + orig->x
                + index % orig->w + (index / orig->w) * picture->w + w + 1];

            /*
            B = picture->pixels[orig->y * orig->w + orig->x
                + index % orig->w + (index / orig->w) * orig->w + 1];
            C = picture->pixels[orig->y * orig->w + orig->x
                + index % orig->w + (index / orig->w) * orig->w + w];
            D = picture->pixels[orig->y * orig->w + orig->x
                + index % orig->w + (index / orig->w) * orig->w + w + 1];
            */

            gray = (int)(A * (1 - x_diff) * (1 - y_diff)
                    + B * (x_diff) * (1 - y_diff)
                    + C * (y_diff) * (1 - x_diff)
                    + D * (x_diff * y_diff));

            //printf("gray = %i\n", gray);
            car[offset++] = gray;
        }
    }

    debug_vectorized_char(car); //draw the letter
    return car;
}

