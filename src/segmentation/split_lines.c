#include "split_lines.h"

unsigned int max(unsigned int a, unsigned int b)
{
    return a > b ? a : b;
}

unsigned int min(unsigned int a, unsigned int b)
{
    return a < b ? a : b;
}

struct s_rectangle* splitLines(struct s_binarypic *picture)
{
    unsigned int i, j, is_white, line_found, left, right;
    size_t current;
    struct s_rectangle *lines;

    current = 0;
    lines = malloc(1 * sizeof(struct s_rectangle));
    line_found = 0;

    for(i = 0; i < picture->h; i++)
    {
        is_white = 1;

        // Left and right are line bounds.
        left = picture->w;
        right = 0;

        for(j = 0; j < picture->w; j++)
        {
            is_white = is_white && picture->pixels[i * picture->w + j];
            if(picture->pixels[i * picture->w + j] == 0)
            {
            }
        }
        if(!is_white)
        {
            if(!line_found)
            {
                lines = realloc(lines,
                        (current + 1) * sizeof(struct s_rectangle));
                lines[current].y = j;
                lines[current].x = left;
                lines[current].w = right;
                current++;
            }
            lines[current - 1].x = min(lines[current - 1].x, left);
            lines[current - 1].w = min(lines[current - 1].w, right);
        }
        if(is_white && line_found)
        {
            lines[current - 1].h = j - lines[current - 1].y;
            lines[current - 1].w = lines[current - 1].w -
                lines[current - 1].x;
        }
        line_found = !is_white;
    }

    return lines;
}
