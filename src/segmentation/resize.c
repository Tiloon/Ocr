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

inline int get_in_bounds(struct s_binarypic *pic,
        struct s_rectangle *bounds, size_t x, size_t y)
{
    if((x > bounds->w) || (y > bounds->h))
        return 1;
    return pic->pixels[(y + bounds->y) * pic->w + x + bounds->x];
}

char* vectorize_char(struct s_binarypic *picture, struct s_rectangle *orig) {
    char *car;
    int A, B, C, D, x, y;
    size_t dim, offset, current;
    float x_ratio, y_ratio, x_diff, y_diff;
    int i, j;

    if(!(car = calloc(CHAR_WIDTH * CHAR_HEIGHT, sizeof(char))))
    {
        LOG_ALLOC_ERR();
        return 0;
    }

    dim = max(orig->w, orig->h);
    x_ratio = ((float)(dim - 1)) / ((float) (CHAR_WIDTH - 1)); // -2 = magic
    y_ratio = ((float)(dim - 1)) / ((float) (CHAR_HEIGHT - 2));
    offset = 0;

    for(i = 0; i < CHAR_HEIGHT; i++)
    {
        for(j = 0; j < CHAR_WIDTH; j++)
        {
            x = (int)(x_ratio * j);
            y = (int)(y_ratio * i);
            x_diff = (x_ratio * j) - x;
            y_diff = (y_ratio * i) - y;

            current = orig->y * picture->w + orig->x;

            A = get_in_bounds(picture, orig, x, y);
            B = get_in_bounds(picture, orig, 1 + x, y);
            C = get_in_bounds(picture, orig, x, y + 1);
            D = get_in_bounds(picture, orig, 1 + x, y + 1);

            car[offset++] = ((A * (1 - x_diff) * (1 - y_diff)
                    + B * (x_diff) * (1 - y_diff)
                    + C * (y_diff) * (1 - x_diff)
                    + D * (x_diff * y_diff)) > 0.5F);
        }
    }

    debug_vectorized_char(car); //draw the letter
    return car;
}

