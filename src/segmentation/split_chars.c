#include "split_chars.h"

    unsigned int max(unsigned int a, unsigned int b)
{
    return a > b ? a : b;
}

unsigned int min(unsigned int a, unsigned int b)
{
    return a < b ? a : b;
}

struct s_rectangle* splitChars(struct s_binarypic picture, 
	struct s_rectangle *line)
{
    unsigned int i, j, is_white, char_found, up, down;
    size_t current;
    struct s_rectangle *chars;

    current = 0;
    chars = malloc(1 * sizeof(struct s_rectangle));
    char_found = 0;

    for(j = line->x; i < line->w; j++)
    {
        is_white = 1;

        // up and down are chars bounds.
        up = picture->h;
        down = 0;

        for(i = line->y; i < line->h; i++)
        {
            // First black pixel we meet
            if(is_white && (picture->pixels[i * picture->w + j] == 0))
                up = i;

            is_white = is_white && picture->pixels[i * picture->w + j];

            // Last black pixel we meet
            if(picture->pixels[i * picture->w + j] == 0)
                down = i;
        }
        if(!is_white)
        {
            if(!char_found)
            {
                chars = realloc(chars,
                        (current + 1) * sizeof(struct s_rectangle));
                chars[current].y = up;
                chars[current].x = j;
                chars[current].h = down;
                current++;
            }
            chars[current - 1].y = min(chars[current - 1].y, up);
            chars[current - 1].h = max(chars[current - 1].h, down);
        }
        if(is_white && char_found)
        {
            chars[current - 1].w = j - chars[current - 1].x;
            chars[current - 1].h = chars[current - 1].h -
                chars[current - 1].y;
        }
        char_found = !is_white;
    }

    chars[current] = 0;

    return chars;
}
