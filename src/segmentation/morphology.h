#ifndef MORPHOLOGY_H
#define MORPHOLOGY_H

#include <stdlib.h>
#include <string.h>

typedef unsigned int uint;

// Rectange erosion/dilatation/opening/closing.
// Rectangle dimensions : x * 2 + 1; y * 2 + 1

int morph_erode(char *pic, uint w, uint h, uint x, uint y);
int morph_dilate(char *pic, uint w, uint h, uint x, uint y);
int morph_close(char *pic, uint w, uint h, uint x, uint y);
int morph_open(char *pic, uint w, uint h, uint x, uint y);

#endif
