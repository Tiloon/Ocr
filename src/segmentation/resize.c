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

/*
 * TTTTTTTTT  OOOO  DDDDD   OOOO
 *     T     O    O D    D O    O     O
 *     T     O    O D    D O    O
 *     T     O    O D    D O    O
 *     T     O    O D    D O    O     O
 *     T      OOOO  DDDDD   OOOO
 *
 * Keep characters ratio (ie consider them as square, and pixels outside orig
 * as white pixels)
 */


char* vectorize_char(struct s_binarypic *picture, struct s_rectangle *orig) {
    char *car;
    int A, B, C, D, x, y, index, gray;
    size_t w, h, offset, current;
    float x_ratio, y_ratio, x_diff, y_diff;
    int i, j;

    if(!(car = calloc(CHAR_WIDTH * CHAR_HEIGHT, sizeof(char))))
    {
        LOG_ALLOC_ERR();
        return 0;
    }

    w = orig->w;
    h = orig->h;
    x_ratio = ((float)(w - 1)) / ((float) (CHAR_WIDTH - 1)); // -2 = magic
    y_ratio = ((float)(h - 1)) / ((float) (CHAR_HEIGHT - 2));
    offset = 0;

    for(i = 0; i < CHAR_HEIGHT; i++)
    {
        for(j = 0; j < CHAR_WIDTH; j++)
        {
            x = (int)(x_ratio * j);
            y = (int)(y_ratio * i);
            x_diff = (x_ratio * j) - x;
            y_diff = (y_ratio * i) - y;
            index = y * w + x;

            current = orig->y * picture->w + orig->x;


            // TODO 80 col
            A = picture->pixels[current + index % orig->w + (index / orig->w) * picture->w];
            B = picture->pixels[current + 1 + index % orig->w + (index / orig->w) * picture->w];
            C = picture->pixels[current + picture->w + index % orig->w + (index / orig->w) * picture->w];
            D = picture->pixels[current + picture->w + 1 + index % orig->w + (index / orig->w) * picture->w];

            gray = ((A * (1 - x_diff) * (1 - y_diff)
                    + B * (x_diff) * (1 - y_diff)
                    + C * (y_diff) * (1 - x_diff)
                    + D * (x_diff * y_diff)) > 0.5F);

            //printf("gray = %i\n", gray);
            car[offset++] = gray;
        }
    }

    debug_vectorized_char(car); //draw the letter
    return car;
}

