#include "learn_from_pics.h"

long double* vector_bool_to_nn(char* vect, size_t size)
{
    size_t i;
    long double *ret;

    ret = calloc(size, sizeof(long double));

    for(i = 0; i < size; i++)
        ret[i] = ((long double) vect[i]) - 0.5;

    return ret;
}

static int segmentation_get_chars(GdkPixbuf *origin, long double ***p_vect,
        size_t char_count)
{
    GdkPixbuf *pixbuf;
    struct s_binarypic *pic;
    struct s_rectangle *chars, *lines, bloc;
    size_t itr_chars, itr_lines, i;
    char *arr;

    if(!(pic = calloc(1, sizeof(struct s_binarypic))))
    {
        LOG_ALLOC_ERR();
        return 0;
    }
    pixbuf = NULL;
    lines = NULL;
    chars = NULL;
    i = 0;

    gdk_to_binary(origin, pic);
    binary_to_gdk(pic, &pixbuf);
    bloc = (struct s_rectangle){.x = 0, .y = 0, .w = pic->w, .h = pic->h};
    lines = split_lines(pic, &bloc);
    if(lines)
    {
        for(itr_lines = 0; lines[itr_lines].h || lines[itr_lines].w;
                itr_lines++)
        {
            chars = split_chars(pic, lines + itr_lines);
            if(chars)
            {
                for(itr_chars = 0; chars[itr_chars].h || chars[itr_chars].w;
                        itr_chars++)
                {
                    arr = vectorize_char(pic, chars + itr_chars);
                    (*p_vect)[i] = vector_bool_to_nn(arr, 256);
                    i++;
                }
            }
            FREE(chars);
        }
    }
    FREE(lines);
    FREE(pic);

    if(i != char_count)
    {
        fprintf(stderr, "Error : chars count (%zu / %zu)\n", i, char_count);
        return -1;
    }

    return 0;
}

long double ***load_image_set(char **files, size_t char_count, size_t *i)
{
    long double ***p_datasets;

    p_datasets = 0;

    for((*i) = 0; files[*i]; (*i)++)
    {
        p_datasets = realloc(p_datasets, ((*i) + 1) * sizeof(char**));
        if(picture_load_from_file(files[(*i)]))
        {
            LOG_ALLOC_ERR();
            return 0;
        }
        p_datasets[*i] = calloc(char_count, sizeof(char*));
        segmentation_get_chars(picture_get_image(), p_datasets + (*i),
                char_count);
    }

    return p_datasets;
}

char **parse_file_cslist(char *str)
{
    size_t i, j;
    char **list;

    if(!str)
        return NULL;

    j = 0;
    list = NULL;
    list = calloc(1, sizeof(char*));
    list[0] = str;

    for(i = 0; str[i]; i++)
        {
            if(str[i] == ',')
            {
                str[i] = 0;
                j++;
                list = realloc(list, (j + 2) * sizeof(char*));
                list[j] = str + i + 1;
            }
        }

    list[j + 1] = NULL;

    return list;
}
