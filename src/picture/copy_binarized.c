#include "copy_binarized.h"

struct s_binarypic *copy_binarypic(struct s_binarypic *origin)
{
    size_t i;
    struct s_binarypic *new;

    new = malloc(sizeof(struct s_binarypic));

    if(new == NULL)
    {
        fprintf(stderr, "Not enough memory to copy binarized picture\n");
        return NULL;
    }
    new->w = origin->w;
    new->h = origin->h;
    new->pixels = malloc((new->w + 1) * (new->h + 1) * sizeof(char));
    for(i = 0; i < (new->h * new->w); i++)
        new->pixels[i] = origin->pixels[i];

    return new;
}
