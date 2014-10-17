#ifndef FILTERS_H
#define FILTERS_H

#include <stdlib.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include "binarypic.h"

int gdk_to_binary(GdkPixbuf *picture, struct s_binarypic *binarypic);
int binary_to_gdk(struct s_binarypic *binarypic, GdkPixbuf *picture);

#endif
