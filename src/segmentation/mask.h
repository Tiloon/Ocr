#ifndef MASK_H
#define MASK_H

#include "../picture/binarypic.h"

char* mask_picture(char to_mask, struct s_binarypic *picture, char *mask);
int mask_local_picture(char to_mask, struct s_binarypic *picture, char *mask);

#endif