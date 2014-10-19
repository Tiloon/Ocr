#include "split_chars.h"

    unsigned int max(unsigned int a, unsigned int b)
{
    return a > b ? a : b;
}

unsigned int min(unsigned int a, unsigned int b)
{
    return a < b ? a : b;
}

struct s_rectangle* splitChars(struct s_binarypic picture,int *tab)
{
    unsigned int i, j, is_white, char_found, up, down;
    size_t current;
    struct s_rectangle *chars;

    current = 0;
    chars = malloc(1 * sizeof(struct s_rectangle));
    char_found = 0;

    for(j = 0; i < picture->w; j++)
    {
        is_white = 1;

        // up and down are chars bounds.
        up = picture->h;
        down = 0;

        for(i = 0; i < picture->h; i++)
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
                chars[current].y = up; //=i
                chars[current].x = j;
                chars[current].h = down; //last j
                current++;
            } //on actualise x et w tant qu'on est sur la même ligne
            chars[current - 1].y = min(chars[current - 1].y, up);
            chars[current - 1].h = max(chars[current - 1].h, down); //max au lieu de min
        }
        if(is_white && char_found)
        {
            chars[current - 1].w = j - chars[current - 1].x; //j => i
            chars[current - 1].h = chars[current - 1].h -
                chars[current - 1].y;
        }
        char_found = !is_white; //=1
    }

    chars[current] = 0;

    return chars;
}
