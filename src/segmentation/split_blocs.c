#include "split_blocs.h"


void findBlockrec(struct s_binarypic *picture, struct s_rectangle *rect,  
        unsigned int i, unsigned int j, int *tab)
{
    if(picture->pixels[i*picture->w+j] == 0)
    {
        if(!tab[i*picture->w+j])
        {
            tab[i*picture->w+j] = 1;
            rect->x = min(j, rect->x);
            rect->y = min(i, rect->y);
            rect->w = max(j, rect->w);
            rect->h = max(i, rect->h);
            /*if(j < rect->x)
                rect->x = j;
            if(j > rect->x + rect->w)
                rect->w = j - rect->x;
            if(i < rect->y)
                rect->y = i;
            if(i > rect->y + rect->h)
                rect->h = i - rect->y;*/
            findBlockrec(picture,rect,i-1,j,tab);
            findBlockrec(picture,rect,i,j-1,tab);
            findBlockrec(picture,rect,i+1,j,tab);
            findBlockrec(picture,rect,i,j+1,tab);
        }
    }
}


struct s_rectangle findBlock(struct s_binarypic *picture, struct s_rectangle *rect,  
        unsigned int i, unsigned int j, int *tab)
{

    if(picture->pixels[i * picture->w + j] == 0)
    {
        if(!tab[i * picture->w + j])
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
            findBlockrec(picture, rect, i - 1, j, tab);
            findBlockrec(picture, rect, i, j - 1, tab);
            findBlockrec(picture, rect, i + 1, j, tab);
            findBlockrec(picture, rect, i, j + 1, tab);
            rect->w -= rect->x;
            rect->h -= rect->y;
        }
    }
    return *rect;
}



int blockFoundXY(unsigned int i, unsigned int j, struct s_rectangle *blockFound, unsigned int nbrBlock)
{
    unsigned int var;

    for(var = 0; var < nbrBlock; var++)
    {
        if(i >= blockFound[var].y 
        && i <= (blockFound[var].y + blockFound[var].h)
        && j >= blockFound[var].x 
        && j <= (blockFound[var].x + blockFound[var].w))
            return 1;
    }
    return 0;
}


struct s_rectangle* splitBlocs(struct s_binarypic *picture)
{
    unsigned int i,j,nbrBlock = 0;
    struct s_rectangle *blockFound = NULL;


    for(i = 0; i < picture->h; i++)
    {
        for(j = 0; j < picture->w; j++)
        {
            if(picture->pixels[i * picture->w + j] == 0 
            && !blockFoundXY(i, j, blockFound, nbrBlock))
            {
                blockFound = realloc(blockFound, (nbrBlock + 2) * sizeof(struct s_rectangle));
                int *tab = malloc(picture->w * picture->h * sizeof(int));//char
                struct s_rectangle *rect = malloc(1 * sizeof(struct s_rectangle));
                rect[0].x = j;
                rect[0].y = i;
                rect[0].w = 0;
                rect[0].h = 0;
                blockFound[nbrBlock] = findBlock(picture, rect, i, j, tab);
                free(tab); 
                free(rect);
                nbrBlock++;
            }
        }
    }
    blockFound[nbrBlock].x = 0;
    blockFound[nbrBlock].y = 0;
    blockFound[nbrBlock].w = 0;
    blockFound[nbrBlock].h = 0;
    return blockFound;
}
