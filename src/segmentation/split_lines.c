#include "split_lines.h"

struct s_rectangle* split_lines(struct s_binarypic *picture,
        struct s_rectangle *bloc)
{
    unsigned int i, j, is_white, line_found, left, right;
    size_t current;
    struct s_rectangle *lines;

    current = 0;
    lines = NULL;
    line_found = 0;

    for(i = bloc->y; i < (bloc->h + bloc->y); i++)
    {
        is_white = 1;

        // Left and right are line bounds.
        left = picture->w;
        right = 0;

        for(j = bloc->x; j < (bloc->x + bloc->w); j++)
        {
            // First black pixel we meet
            if(is_white && (picture->pixels[i * picture->w + j] == 0))
                left = j;

            is_white = is_white && picture->pixels[i * picture->w + j];

            // Last black pixel we meet
            if(picture->pixels[i * picture->w + j] == 0)
                right = j;
        }
        if(!is_white)
        {
            if(!line_found)
            {
                lines = realloc(lines,
                        (current + 2) * sizeof(struct s_rectangle));
                lines[current].y = i;
                lines[current].x = left;
                lines[current].w = right;
                current++;
            }
            lines[current - 1].x = min(lines[current - 1].x, left);
            lines[current - 1].w = max(lines[current - 1].w, right);
        }
        if(is_white && line_found)
        {
            lines[current - 1].h = i - lines[current - 1].y;
            lines[current - 1].w = lines[current - 1].w -
                lines[current - 1].x;
        }
        line_found = !is_white;
    }

    lines[current].x = 0;
    lines[current].y = 0;
    lines[current].w = 0;
    lines[current].h = 0;

    return lines;
}
