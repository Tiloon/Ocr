#ifndef LEARN_FROM_PICS_H
#define LEARN_FROM_PICS_H

#include "../redef.h"
#include "../main.h"

long double* vector_bool_to_nn(char* vect, size_t size);
char **parse_file_cslist(char *str);
long double ***load_image_set(char **files, size_t char_count, size_t *nb_font);

#endif
