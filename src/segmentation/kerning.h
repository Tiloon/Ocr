#ifndef KERNING_H
#define KERNING_H

#include <stdlib.h>
#include <stdio.h>
#include "../picture/binarypic.h"
#include "rectangle.h"

struct s_binarypic* kerning(struct s_binarypic *picture,
        struct s_rectangle *chars);

#endif
