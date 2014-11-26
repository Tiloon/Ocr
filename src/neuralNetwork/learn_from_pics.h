#ifndef LEARN_FROM_PICS_H
#define LEARN_FROM_PICS_H

#include "../redef.h"
#include "../main.h"

char **parse_file_cslist(char *str);
char ***load_image_set(char **files, size_t char_count);

#endif
