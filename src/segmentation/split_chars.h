#ifndef SPLIT_CHARS_H
#define SPLIT_CHARS_H

#include <stdlib.h>
#include "../picture/binarypic.h"
#include "rectangle.h"

struct s_rectangle * splitChars(struct s_binarypic *picture,
        struct s_rectangle *lines);

#endif
