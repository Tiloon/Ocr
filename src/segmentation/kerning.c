#include "kerning.h"

struct s_point
{
    unsigned int x, y;
    int x1, x2;
};

int debug(struct s_binarypic *picture)
{
    for(size_t i = 0; i < picture->h; i++)
    {
        for(size_t j = 0; j < picture->w; j++)
        {
            printf("%i", picture->pixels[i*picture->w+j]);
        }
        printf("\n");
    }
    printf("endchar\n");
    return 0;
}

int copy_block(struct s_binarypic *picture, struct s_binarypic *rep,
        unsigned int i, unsigned int j, char* alreadyUsed,
        struct s_rectangle *rect, float size)
{
    struct s_point *points;
    size_t top;
    int x, y, varx = 0, vary = 0;
    x = (j - rect->x)*size;
    y = (i - rect->y);
    alreadyUsed[(i)*picture->w+j] = 1;
    top = 1;
    rep->pixels[(y+varx)*rep->w+x+vary] = 1;

    points = calloc(2, sizeof(struct s_point));

    points[0] = (struct s_point) {i, j, 0, 0};

    while(top > 0)
    {
        top--;
        i = points[top].x;
        j = points[top].y;
        varx = points[top].x1;
        vary = points[top].x2;

        rep->pixels[(y + varx) * rep->w + x + vary] =
            !picture->pixels[i * picture->w + j];

        if((i > rect->y) &&
                !alreadyUsed[(i - 1) * picture->w + j] &&
                !picture->pixels[(i - 1) * picture->w + j])
        {
            alreadyUsed[(i-1) * picture->w + j] = 1;
            points = realloc(points, sizeof(struct s_point) * (top + 1));
            points[top] = (struct s_point) {i - 1, j, varx-1, vary};
            top++;
        }
        if((j > rect->x) &&
                !alreadyUsed[(i) * picture->w + j - 1] &&
                !picture->pixels[i * picture->w + j - 1])
        {
            alreadyUsed[(i) * picture->w + j - 1] = 1;
            points = realloc(points, sizeof(struct s_point) * (top + 1));
            points[top] = (struct s_point) {i, j - 1, varx, vary-1};
            top++;
        }
        if((i < rect->y + rect->h) &&
                !alreadyUsed[(i + 1) * picture->w + j] &&
                !picture->pixels[(i + 1) * picture->w + j])
        {
            alreadyUsed[(i+1) * picture->w + j] = 1;
            points = realloc(points, sizeof(struct s_point) * (top + 1));
            points[top] = (struct s_point) {i + 1, j, varx+1, vary};
            top++;
        }
        if((j < rect->x + rect->w) &&
                !alreadyUsed[(i) * picture->w + j + 1] &&
                !picture->pixels[i * picture->w + j + 1])
        {
            alreadyUsed[(i) * picture->w + j + 1] = 1;
            points = realloc(points, sizeof(struct s_point) * (top + 1));
            points[top] = (struct s_point) {i, j + 1, varx, vary+1};
            top++;
        }

    }
    free(points);

    return 1;
}

struct s_binarypic* copy_kerning(struct s_binarypic *picture,
        struct s_rectangle *chars, struct s_binarypic *rep, float size)
{//apply copy_block every time it finds a new block
    unsigned int i, j;
    char* alreadyUsed = calloc(picture->w*picture->h, sizeof(char));
    for(i = chars->y; i < chars->h + chars->y; i++)
    {
        for(j = chars->x; j < chars->w + chars->x; j++)
        {
            if(!picture->pixels[i*picture->w+j] &&
                    !alreadyUsed[(i)*picture->w+j])
            {
                copy_block(picture, rep, i, j, alreadyUsed, chars, size);
            }
        }
    }

    free(alreadyUsed);

    return rep;
}

struct s_binarypic* kerning(struct s_binarypic *picture,
        struct s_rectangle *chars)
{
    unsigned int i, j;
    float size = 1.5;
    struct s_binarypic* res = calloc(1, sizeof(struct s_binarypic));
    if(!chars->w || !chars->h)
    {
        res->pixels = calloc(10,sizeof(struct s_binarypic));
        return res;
    }
    res->pixels = calloc(size*chars->w*chars->h,
            sizeof(struct s_binarypic));
    res->w = size*chars->w;
    res->h = chars->h;

    res = copy_kerning(picture, chars, res, size);
    for(i = 0; i < res->h; i++)
    {
        for(j = 0; j < res->w; j++)
        {
            res->pixels[i*res->w+j] = !res->pixels[i*res->w+j];
        }
    }

    return res;

}
