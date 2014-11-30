#ifndef SPLIT_CHARS_H
#define SPLIT_CHARS_H

#include <stdlib.h>
#include <stdio.h>
#include "../picture/binarypic.h"
#include "rectangle.h"

struct s_rectangle * split_chars(struct s_binarypic *picture,
        struct s_rectangle *line);
size_t* get_spaces(struct s_rectangle *car);

#endif
