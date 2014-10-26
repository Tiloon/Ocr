#ifndef SPLIT_LINES_H
#define SPLIT_LINES_H

#include <stdlib.h>
#include "../picture/binarypic.h"
#include "rectangle.h"

struct s_rectangle* split_lines(struct s_binarypic *picture,
        struct s_rectangle *bloc);

#endif
