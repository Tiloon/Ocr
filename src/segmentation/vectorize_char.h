#ifndef RESIZE_H
#define RESIZE_H

#include <stdlib.h>

#include "../redef.h"
#include "../picture/binarypic.h"
#include "../neuralNetwork/consts.h"
#include "rectangle.h"

char* vectorize_char(struct s_binarypic *picture, struct s_rectangle *orig); 

#endif
