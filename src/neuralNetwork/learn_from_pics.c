#include "learn_from_pics.h"

static int segmentation_get_chars(GdkPixbuf *origin, long double ***p_vect,
        size_t char_count)
{
    GdkPixbuf *pixbuf;
    struct s_binarypic *pic, *mask;
    struct s_rectangle *chars, *lines, *blocs;
    size_t itr_chars, itr_lines, itr_blocs, i, j;
    char *arr;

    mask = NULL;
    if(!(pic = calloc(1, sizeof(struct s_binarypic))))
    {
        LOG_ALLOC_ERR();
        return 0;
    }
    pixbuf = NULL;
    blocs = NULL;
    lines = NULL;
    chars = NULL;
    i = 0;

    gdk_to_binary(origin, pic);
    binary_to_gdk(pic, &pixbuf);
    mask = copy_binarypic(pic);
    // TODO : change constants to some document size function
    morph_erode(mask->pixels, mask->w, mask->h, 12, 12);

    blocs = split_blocs(mask);

    if(!blocs)
        return -1;

    for(itr_blocs = 0; blocs[itr_blocs].h || blocs[itr_blocs].w; itr_blocs++)
    {
        lines = split_lines(pic, blocs + itr_blocs);
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
                        if(i > char_count)
                        {
                            fprintf(stderr, "Error : too much chars\n");
                            return -1;
                        }
                        arr = vectorize_char(pic, chars + itr_chars);
                        (*p_vect)[i] = calloc(256, sizeof(long double));
                        for(j = 0; j < 256; j++)
                            (*p_vect)[i][j] = ((long double)arr[j]) - 0.5;
                        draw_rectangle(pixbuf, chars + itr_chars, ~0, 0, 0);
                    }
                }
                FREE(chars);
            }
        }
        FREE(lines);
    }
    FREE(blocs);
    FREE(pic);


    if(i + 1 < char_count)
    {
        fprintf(stderr, "Error : too much chars\n");
        return -1;
    }

    return 0;
}

long double ***load_image_set(char **files, size_t char_count)
{
    size_t i;
    long double ***p_datasets;

    p_datasets = 0;

    for(i = 0; files[i]; i++)
    {
        p_datasets = realloc(p_datasets, (i + 1) * sizeof(char**));
        if(picture_load_from_file(files[i]))
        {
            LOG_ALLOC_ERR();
            return 0;
        }
        p_datasets[i] = calloc(char_count, sizeof(char*));
        segmentation_get_chars(picture_get_image(), p_datasets + i, char_count);
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

    for(i = 0; str[i]; i++) // on créé la liste des str qui finissent par ,
    {
        if(str[i] == ',')
        {
            str[i] = 0;
            j++;
            list = realloc(list, (j + 2) * sizeof(char*));
            list[j] = str + i + 1;
        }
    }

    list[j + 1] = NULL; // On marque la fin de la liste

    return list;
}