#ifndef FILTERS_H
#define FILTERS_H

#include <stdlib.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include "binarypic.h"

int imgToBinary(GdkPixbuf *picture, struct s_binarypic *binarypic);

#endif
