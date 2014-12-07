#include "split_chars.h"

unsigned int get_step(struct s_rectangle *car)
{
    int i;
    unsigned int rep = 0;

    for(i = 0; car[i + 1].h || car[i + 1].w; i++)
    {
        //printf("calculating step, i+1.x = %i, i.x = %i, i.w = %i\n", car[i+1].x, car[i].x, car[i].w);
        rep += car[i + 1].x - car[i].x - car[i].w;
    }
    return rep / i;
}

size_t* get_spaces(struct s_rectangle *car)
{
    size_t l, i, k, step, *rep;
    if(!car || !car[0].h || !car[0].w || !car[1].h || !car[1].w)
        return calloc(1,sizeof(size_t)); //0 or 1  car, no spaces

    //unsigned int step = 8;
    step = get_step(car) * 1.2;

    for(l = 0; car[l].h || car[l].w;l++); //get lenght

    rep = calloc(l, sizeof(size_t));
    k = 0;

    //printf("step = %i\n", step);
    for(i = 0; car[i + 1].h || car[i + 1].w; i++)
    {
        //printf("current space = %i\n", car[i+1].x - car[i].x - car[i].w);
        if(car[i + 1].x - car[i].x - car[i].w >= step)
        {
            //printf("k = %i and i = %zu\n", k, i);
            rep[k++] = i + 1;
        }
    }
    return rep;
}

struct s_rectangle* split_chars(struct s_binarypic *picture,
        struct s_rectangle *line)
{
    unsigned int i, j, is_white, char_found, up, down;
    size_t current;
    struct s_rectangle *chars;

    current = 0;
    chars = NULL;
    char_found = 0;

    for(j = line->x; j < (line->x + line->w); j++)
    {
        is_white = 1;

        // up and down are chars bounds.
        up = picture->h;
        down = 0;

        for(i = line->y; i < (line->y + line->h); i++)
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
                        (current + 2) * sizeof(struct s_rectangle));
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
    if(char_found)
    {
        chars[current - 1].w = j - chars[current - 1].x;
        chars[current - 1].h = chars[current - 1].h -
            chars[current - 1].y;
    }
    //chars = realloc(chars, (current + 1) * sizeof(struct s_rectangle));
    if((current == 0) || (chars == NULL))
        return NULL;
    chars[current].w = 0;
    chars[current].x = 0;
    chars[current].y = 0;
    chars[current].h = 0;

    return chars;
}
