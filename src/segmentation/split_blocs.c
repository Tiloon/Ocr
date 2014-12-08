#include "split_blocs.h"

struct s_point
{
    unsigned int x, y;
};

int find_bloc(struct s_binarypic *picture,
        struct s_rectangle *rect, unsigned int i, unsigned int j, char *tab)
{
    struct s_point *points;
    size_t top;

    if((!picture->pixels[i * picture->w + j]) &&
            (tab[i * picture->w + j]))
        return 0;

    top = 1;
    if(!(points = calloc(1, sizeof(struct s_point))))
    {
        LOG_ALLOC_ERR();
        return 0;
    }

    points[0] = (struct s_point) {i, j};

    while(top > 0)
    {
        top--;
        i = points[top].x;
        j = points[top].y;
        tab[i * picture->w + j] = 1;
        rect->x = min(j, rect->x);
        rect->y = min(i, rect->y);
        rect->w = max(j, rect->w);
        rect->h = max(i, rect->h);

        if((i > 0) &&
                !tab[(i - 1) * picture->w + j] &&
                !picture->pixels[(i - 1) * picture->w + j])
        {
            tab[(i-1) * picture->w + j] = 1;
            points = realloc(points, sizeof(struct s_point) * (top + 1));
            points[top] = (struct s_point) {i - 1, j};
            top++;
        }
        if((j > 0) &&
                !tab[i * picture->w + j - 1] &&
                !picture->pixels[i * picture->w + j - 1])
        {
            tab[i * picture->w + j-1] = 1;
            points = realloc(points, sizeof(struct s_point) * (top + 1));
            points[top] = (struct s_point) {i, j - 1};
            top++;
        }
        if((i < picture->h) &&
                !tab[(i + 1) * picture->w + j] &&
                !picture->pixels[(i + 1) * picture->w + j])
        {
            tab[(i+1) * picture->w + j] = 1;
            points = realloc(points, sizeof(struct s_point) * (top + 1));
            points[top] = (struct s_point) {i + 1, j};
            top++;
        }
        if((j < picture->w) &&
                !tab[i * picture->w + j + 1] &&
                !picture->pixels[i * picture->w + j + 1])
        {
            tab[i * picture->w + j+1] = 1;
            points = realloc(points, sizeof(struct s_point) * (top + 1));
            points[top] = (struct s_point) {i, j + 1};
            top++;
        }
    }

    FREE(points);
    rect->w -= rect->x;
    rect->h -= rect->y;

    return 1;
}

int bloc_found(unsigned int i, unsigned int j,
        struct s_rectangle *blocs, unsigned int nb_bloc)
{
    unsigned int itr;

    for(itr = 0; itr < nb_bloc; itr++)
    {
        if(i >= blocs[itr].y
                && i <= (blocs[itr].y + blocs[itr].h)
                && j >= blocs[itr].x
                && j <= (blocs[itr].x + blocs[itr].w))
            return 1;
    }
    return 0;
}


struct s_rectangle* get_blocs(struct s_binarypic *picture)
{
    unsigned int i, j, nb_bloc;
    struct s_rectangle *blocs;
    char *tab;

    nb_bloc = 0;
    blocs = NULL;

    if(!(tab = calloc((picture->w + 1) * (picture->h + 1), sizeof(char))))
    {
        LOG_ALLOC_ERR();
        return 0;
    }

    for(i = 0; i < picture->h; i++)
    {
        for(j = 0; j < picture->w; j++)
        {
            if((picture->pixels[i * picture->w + j] == 0)
                    && !bloc_found(i, j, blocs, nb_bloc))
            {
                if(!(blocs = realloc(blocs, (nb_bloc + 2) *
                                sizeof(struct s_rectangle))))
                {
                    fprintf(stderr, "Malloc error %s:%i\n", __FILE__,
                            __LINE__);
                    return 0;
                }

                blocs[nb_bloc].x = j;
                blocs[nb_bloc].y = i;
                blocs[nb_bloc].w = 0;
                blocs[nb_bloc].h = 0;

                find_bloc(picture, blocs + nb_bloc, i, j, tab);

                nb_bloc++;
            }
        }
    }
    FREE(tab);
    tab = NULL;

    if(blocs == NULL)
        return NULL;
    blocs[nb_bloc].x = 0;
    blocs[nb_bloc].y = 0;
    blocs[nb_bloc].w = 0;
    blocs[nb_bloc].h = 0;
    return blocs;
}


struct s_rectangle *split_blocs(struct s_binarypic *picture)
{
    struct s_binarypic *mask;

    mask = copy_binarypic(picture);
    morph_erode(mask->pixels, mask->w, mask->h, mask->w / 120,
            mask->h / 120);
    return get_blocs(mask);
}
