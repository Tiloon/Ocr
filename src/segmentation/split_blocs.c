#include "split_blocs.h"

/*void find_bloc_rec(struct s_binarypic *picture, struct s_rectangle *rect,
        unsigned int i, unsigned int j, char *tab)
{
    //if(picture->pixels[i * picture->w + j] == 0)
    {
        //if(!tab[i * picture->w + j])
        {
            //tab[i * picture->w + j] = 1;
            rect->x = min(j, rect->x);
            rect->y = min(i, rect->y);
            rect->w = max(j, rect->w);
            rect->h = max(i, rect->h);
            if(i>0 && picture->pixels[(i-1) * picture->w + j] == 0)
            {
                tab[(i-1) * picture->w + j] = 1;
                find_bloc_rec(picture, rect, i - 1, j, tab);
            }
            if(j>0 && picture->pixels[i * picture->w + j-1] == 0)
            {
                tab[i * picture->w + j-1] = 1;
                find_bloc_rec(picture, rect, i, j - 1, tab);
            }
            if(i+1<=picture->h && picture->pixels[(i+1) * picture->w + j] == 0)
            {
                tab[(i+1) * picture->w + j] = 1;
                find_bloc_rec(picture, rect, i + 1, j, tab);
            }
            if(j+1<=picture->w && picture->pixels[i * picture->w + j+1] == 0)
            {
                tab[i * picture->w + j+1] = 1;
                find_bloc_rec(picture, rect, i, j + 1, tab);
            }
        }
    }
}

struct s_rectangle find_bloc(struct s_binarypic *picture,
        struct s_rectangle *rect, unsigned int i, unsigned int j, char *tab)
{
    //if(picture->pixels[i * picture->w + j] == 0)
    {
        //if(!tab[i * picture->w + j])
        {
            tab[i*picture->w+j] = 1;
            if(j<rect->x)
                rect->x = j;
            if(j>rect->x+rect->w)
                rect->w = j - rect->x;
            if(i<rect->y)
                rect->y = i;
            if(i>rect->y+rect->h)
                rect->h = i - rect->y;

            if(i>0)
                find_bloc_rec(picture, rect, i - 1, j, tab);
            if(j>0)
                find_bloc_rec(picture, rect, i, j - 1, tab);
            if(i+1<=picture->h)
                find_bloc_rec(picture, rect, i + 1, j, tab);
            if(j+1<=picture->w)
                find_bloc_rec(picture, rect, i, j + 1, tab);

            //find_bloc_rec(picture, rect, i - 1, j, tab);
              find_bloc_rec(picture, rect, i, j - 1, tab);
              if(i+1<=picture->h)
              find_bloc_rec(picture, rect, i + 1, j, tab);
              if(j+1<=picture->w)
              find_bloc_rec(picture, rect, i, j + 1, tab);*/
            /*rect->w -= rect->x;
            rect->h -= rect->y;
        }
    }
    return *rect;
}*/

struct s_rectangle find_bloc(struct s_binarypic *picture,
        struct s_rectangle *rect, unsigned int i, unsigned int j, char *tab)
{
    struct pile *p = malloc(2 * sizeof(struct pile));
    struct duet *sub;
    struct duet *duet = malloc(1 * sizeof(struct duet));

    duet->i = i;
    duet->j = j;

    pile_init(p);
    add(duet, p);
    tab[i*picture->w+j] = 1;
    while(!isempty(p))
    {
        sub = rmv(p);
        i = sub->i;
        j = sub->j;
        printf("i = %i\n", i);
        printf("j = %i\n", j);
        if(j<rect->x)
            rect->x = j;
        if(j>rect->x+rect->w)
            rect->w = j - rect->x;
        if(i<rect->y)
            rect->y = i;
        if(i>rect->y+rect->h)
            rect->h = i - rect->y;


        if(i > 0 && picture->pixels[(i-1) * picture->w + j] == 0 
                && !tab[(i-1)*picture->w + j])
        {
            tab[(i-1) * picture->w + j] = 1;
            duet->i = i-1;
            add(duet, p);
            duet->i = i+1;
        }
        if(j > 0 && picture->pixels[(i) * picture->w + j-1] == 0 
                && !tab[i*picture->w + j-1])
        {
            tab[(i) * picture->w + j-1] = 1;
            duet->i = j-1;
            add(duet, p);
            duet->i = j+1;
        }
        if(i+1<=picture->h && picture->pixels[(i+1) * picture->w + j] == 0 
                && !tab[(i+1)*picture->w + j])
        {
            tab[(i+1) * picture->w + j] = 1;
            duet->i = i+1;
            add(duet, p);
            duet->i = i-1;
        }
        if(j+1<=picture->w && picture->pixels[(i) * picture->w + j+1] == 0 
                && !tab[i*picture->w + j+1])
        {
            tab[(i) * picture->w + j+1] = 1;
            duet->i = j+1;
            add(duet, p);
            duet->i = j-1;
        }

    }
    free(duet);
    free(p);
    return *rect;

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


struct s_rectangle* split_blocs(struct s_binarypic *picture)
{
    unsigned int i, j, nb_bloc;
    struct s_rectangle *blocs, rect;
    char *tab;

    nb_bloc = 0;
    blocs = NULL;

    for(i = 0; i < picture->h; i++)
    {
        for(j = 0; j < picture->w; j++)
        {
            if(picture->pixels[i * picture->w + j] == 0
                    && !bloc_found(i, j, blocs, nb_bloc))
            {
                blocs = realloc(blocs, (nb_bloc + 2) *
                        sizeof(struct s_rectangle));
                tab = malloc(picture->w * picture->h * sizeof(char));//char

                rect.x = j;
                rect.y = i;
                rect.w = 0;
                rect.h = 0;

                blocs[nb_bloc] = find_bloc(picture, &rect, i, j, tab);

                free(tab);

                nb_bloc++;
            }
        }
    }
    blocs[nb_bloc].x = 0;
    blocs[nb_bloc].y = 0;
    blocs[nb_bloc].w = 0;
    blocs[nb_bloc].h = 0;
    return blocs;
}
