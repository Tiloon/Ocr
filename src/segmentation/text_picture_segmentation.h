#ifndef PICTUREPROCESSING_H
#define PICTUREPROCESSING_H

#include <stdlib.h>
#include <string.h>
#include "morphology.h"

int text_image_segmentation(char *pic, uint w, uint h, char **mask);

#endif
