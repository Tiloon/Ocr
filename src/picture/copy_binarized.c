#include "copy_binarized.h"

struct s_binarypic *copy_binarypic(struct s_binarypic *origin)
{
    size_t i;
    struct s_binarypic *new;

    if(!(new = calloc(1, sizeof(struct s_binarypic))))
    {
        LOG_ALLOC_ERR();
        return 0;
    }

    new->w = origin->w;
    new->h = origin->h;
    if(!(new->pixels = calloc((new->w + 1) * (new->h + 1), sizeof(char))))
    {
        LOG_ALLOC_ERR();
        FREE(new);
        return 0;
    }
    for(i = 0; i < (new->h * new->w); i++)
        new->pixels[i] = origin->pixels[i];

    return new;
}
