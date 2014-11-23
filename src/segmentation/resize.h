#ifndef RESIZE_H
#define RESIZE_H

#include <stdlib.h>
#include "../picture/binarypic.h"
#include "rectangle.h"

#define CHAR_WIDTH 16
#define CHAR_HEIGHT 16

char* vectorize_char(struct s_binarypic *picture, struct s_rectangle *orig); 

#endif
