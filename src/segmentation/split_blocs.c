#include "split_blocs.h"


void findBlockrec(struct s_binarypic *picture, struct s_rectangle *rect,  
                    unsigned int i, unsigned int j, int *tab)
{
    if(picture->pixels[i*picture->w+j] == 0)
    {
        if(!tab[i*picture->w+j])
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
            findBlockrec(picture,rect,i+1,j,tab);
            findBlockrec(picture,rect,i-1,j,tab);
            findBlockrec(picture,rect,i,j+1,tab);
            findBlockrec(picture,rect,i,j-1,tab);
        }
    }
}


struct s_rectangle findBlock(struct s_binarypic *picture, struct s_rectangle *rect,  
                                unsigned int i, unsigned int j, int *tab)
{

    if(picture->pixels[i*picture->w+j] == 0)
    {
        if(!tab[i*picture->w+j])
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
            findBlockrec(picture,rect,i+1,j,tab);
            findBlockrec(picture,rect,i-1,j,tab);
            findBlockrec(picture,rect,i,j+1,tab);
            findBlockrec(picture,rect,i,j-1,tab);
        }
    }
    return *rect;
}



int blockFoundX(unsigned int i, struct s_rectangle *blockFound, unsigned int nbrBlock)
{
    unsigned int var;

    for(var = 0;var<nbrBlock;var++)
    {
        if(i>=blockFound[var].y&&i<=(blockFound[var].y+blockFound[var].h))
            return 1;
    }
    return 0;
}


int blockFoundY(unsigned int j, struct s_rectangle *blockFound, unsigned int nbrBlock)
{
    unsigned int var;

    for(var = 0;var<nbrBlock;var++)
    {
        if(j>=blockFound[var].y&&j<=(blockFound[var].y+blockFound[var].h))
            return 1;
    }
    return 0;
}


struct s_rectangle* splitBlocs(struct s_binarypic *picture)
{
    unsigned int i,j,nbrBlock = 0;
    struct s_rectangle *blockFound = NULL;


    for(i = 0;i< picture->h && !blockFoundX(i, blockFound, nbrBlock);i++)
    {
        for(j = 0;j<picture->w && !blockFoundY(j, blockFound, nbrBlock);j++)
        {
            if(picture->pixels[i*picture->w+j] == 0)
            {
                blockFound = realloc(blockFound, (nbrBlock+1)*sizeof(struct s_rectangle));
                int *tab = malloc(picture->w*picture->h*sizeof(int));
                struct s_rectangle *rect = malloc(1*sizeof(struct s_rectangle));
                rect[0].x = j;
                rect[0].y = i;
                rect[0].w = 1;
                rect[0].h = 1;
                blockFound[nbrBlock] = findBlock(picture,rect, i,j,tab);
                free(tab); //a check
                free(rect);
                nbrBlock++;
                //blockFound = realloc (blockFound, 1*sizeof(int));
            }
        }
    }
    return blockFound;
}
